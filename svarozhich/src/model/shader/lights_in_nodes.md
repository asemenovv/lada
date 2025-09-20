Отличный вопрос для узла-редактора! Ключ — так смоделировать «свет» в графе, чтобы художнику не пришлось заниматься циклами и массивами, а рантайм мог масштабироваться (1…N источников).

Как подружить «несколько источников» и нодовый граф

1) Договор о данных из движка → шейдер

Минимальный и «редактеро-дружелюбный» контракт:
•	UBO/SSBO со светами

~~~cpp
struct PointLight {
vec4 position;    // xyz, w=1
vec4 color;       // rgb, a = intensity
vec4 attenuation; // kc, kl, kq, _
};

layout(set=0, binding=0) uniform Global {
mat4  view;
mat4  proj;
vec4  ambient;            // rgb * intensity
vec4  dirLightDir_Int;    // xyz, w = intensity
vec4  dirLightColor;      // rgb, a = unused
int   numPointLights;
} ubo;

// Вариант А: фиксированный массив (просто)
layout(set=0, binding=1) uniform Lights {
PointLight pointLights[32]; // максимум
} L;

// Вариант Б: SSBO (масштабируемый)
// layout(std430, set=0, binding=1) buffer Lights { PointLight pointLights[]; } L;
~~~


• Материал/граф выдает: baseColor, normalWS, roughness, metallic, emissive, ao, opacity, + опционально clearCoat, specularColor и т. п.

2) Узлы графа: что видеть в редакторе

Чтобы не тащить цикл в UI, делим на «семантические» узлы:
•	Surface / Material Output
Входы: Albedo, Normal, Roughness, Metallic, Emissive, AO.
Выход: финальный vec3/vec4 цвета.
•	Directional Light (виртуальный узел, без параметров)
Логически представляет «солнечный» свет из ubo.dirLight*. Возвращает вклад diffuse, specular (или целиком lighting), чтобы можно было смешать/умножить на альбедо.
•	Point Lights Accumulate (главный трюк)
Узел, который внутри шейдер-генератора разворачивается в цикл по массиву светов и суммирует вклад.
Входы: normalWS, viewDirWS, roughness, metallic, albedo (или split на diffuse/specular lobe).
Параметры: лимит N (для мобильных), включение теней/IES/затухания.
Выходы: diffuseAccum, specularAccum (или сразу lightingAccum).
•	BRDF (узел/функция)
Универсальная функция: принимает N, V, L, F0/roughness/metallic и возвращает diffuse, specular. Её используют и Directional, и Accumulate.
•	Ambient / IBL (позже)
Узлы для ambient, SH/irradiance, specular IBL (prefilter + BRDF LUT).

В UI художник тянет провода «из Directional» и «из PointLights Accumulate» в Material Output. Циклов не видно — всё прячется в одном узле-агрегаторе.

3) Шаблон генерации кода (forward, Blinn/Disney)

Внутри узла «Point Lights Accumulate» вы генерируете что-то такое:

~~~cpp
struct BRDFResult { vec3 diff; vec3 spec; };

BRDFResult evalBRDF(vec3 N, vec3 V, vec3 L, vec3 baseColor, float roughness, float metallic);

// Directional
vec3 shadeDirectional(vec3 N, vec3 V, vec3 baseColor, float roughness, float metallic) {
vec3 Ld = normalize(ubo.dirLightDir_Int.xyz);
float NdotL = max(dot(N, Ld), 0.0);
if (NdotL <= 0.0) return vec3(0.0);

    BRDFResult r = evalBRDF(N, V, Ld, baseColor, roughness, metallic);
    float I = ubo.dirLightDir_Int.w;
    return (r.diff + r.spec) * ubo.dirLightColor.rgb * I * NdotL;
}

// Point lights accumulate
vec3 shadePoints(vec3 P, vec3 N, vec3 V, vec3 baseColor, float roughness, float metallic) {
vec3 sum = vec3(0.0);
int count = min(ubo.numPointLights, 32); // или length(L.pointLights) для SSBO
for (int i = 0; i < count; ++i) {
PointLight Lp = L.pointLights[i];

        vec3 Lvec = Lp.position.xyz - P;
        float dist = length(Lvec);
        vec3 Ldir = (dist > 0.0) ? Lvec / dist : vec3(0,0,1);

        float NdotL = max(dot(N, Ldir), 0.0);
        if (NdotL <= 0.0) continue;

        // attenuation
        float att = 1.0 / (Lp.attenuation.x + Lp.attenuation.y*dist + Lp.attenuation.z*dist*dist);

        BRDFResult r = evalBRDF(N, V, Ldir, baseColor, roughness, metallic);
        float I = Lp.color.a; // intensity
        vec3  C = Lp.color.rgb;

        sum += (r.diff + r.spec) * C * (I * att * NdotL);
    }
    return sum;
}
~~~

А финальный материал собирает всё:

~~~glsl
vec3 N = normalize(normalWS);
vec3 V = normalize(cameraPosWS - P);
vec3 base = baseColor; // из графа/текстур
float r = roughness, m = metallic;

vec3 L_ambient = ubo.ambient.rgb; // или IBL узлы
vec3 L_dir     = shadeDirectional(N,V,base,r,m);
vec3 L_points  = shadePoints(P,N,V,base,r,m);
vec3 L_emissive= emissive;

vec3 color = L_ambient * base + L_dir + L_points + L_emissive;
~~~

4) Как это выглядит в узлах (UX)
   •	Texture → BaseColor → Material Output.Albedo
   •	NormalMap → TBN → Material Output.Normal
   •	Числовые слайдеры → Roughness, Metallic
   •	Directional Light (чёрный ящик) → Lighting
   •	Point Lights Accumulate (чёрный ящик) → Lighting
   •	Add/Mix узлы складывают вклады, подаются в Material Output.ShadedColor

Художник не видит «сколько» огней — граф стабилен, движок просто меняет numPointLights и буфер.

5) Масштабирование и производительность
   •	Forward+ / Clustered: вместо массива всех огней — в UBO/SSBO передавать компактный список огней для текущего кластера/тайла (индирект-буферы). Узел «Accumulate» при генерации кода использует этот список.
   •	Максимумы: для мобильных — лимитировать N в материальном шейдере (или делать несколько вариантов по define).
   •	Мат-варианты: для «Unlit» пропускать вызовы счётных узлов.
   •	Шadows позже: в Accumulate добавить опциональный сэмпл шадоу-карты (пер-тип): точечные — cubemap depth, направленный — каскады.

6) Когда лучше «Deferred»

Если планируется сотни источников в кадре, удобнее генерировать материал-pass (G-buffer) + отдельный lighting-pass (экранные полупрозрачные объёмы/фуллскрин), а узлы света сводить к BRDF и входам из G-buffer. Но как старт — forward/forward+ с «Accumulate» узлом проще.

7) Важные мелочи для граф-генератора
   •	Стабильные имена функций (evalBRDF, shadePoints) и единый include, чтобы разные материалы делили один код.
   •	Фича-флаги из графа → #define USE_NORMALMAP, USE_IBL, USE_CLEARCOAT для тонкой компиляции.
   •	Проверка типов в графе: normal в WS, не в TS; baseColor — линейный цвет.
   •	Параметры света в UI: интенсивность в люменах/канделах → конвертируйте в движке, а в шейдер отдавайте уже нормализованное.

⸻

Если хочешь, накину «микро-DSL» для сериализации этих узлов в YAML (узел Accumulate как «встроенный оператор»), и покажу, как ваш генератор по YAML соберёт финальный GLSL.