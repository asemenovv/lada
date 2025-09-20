# Как подружить несколько источников света и нодовый граф

Ключевая идея — смоделировать **свет** в графе так, чтобы художнику не пришлось заниматься циклами и массивами, а рантайм мог масштабироваться (1…N источников).

---

## 1. Контракт данных «движок → шейдер»

### Структура источника света
```glsl
struct PointLight {
    vec4 position;    // xyz, w=1
    vec4 color;       // rgb, a = intensity
    vec4 attenuation; // kc, kl, kq, _
};
```

### Глобальный UBO
```glsl
layout(set=0, binding=0) uniform Global {
    mat4  view;
    mat4  proj;
    vec4  ambient;            // rgb * intensity
    vec4  dirLightDir_Int;    // xyz, w = intensity
    vec4  dirLightColor;      // rgb, a = unused
    int   numPointLights;
} ubo;
```

### Вариант А: фиксированный массив
```glsl
layout(set=0, binding=1) uniform Lights {
    PointLight pointLights[32];
} L;
```

### Вариант Б: SSBO (масштабируемый)
```glsl
layout(std430, set=0, binding=1) buffer Lights {
    PointLight pointLights[];
} L;
```

Материал/граф должен выдавать: `baseColor`, `normalWS`, `roughness`, `metallic`, `emissive`, `ao`, `opacity`, опционально `clearCoat`, `specularColor` и др.

---

## 2. Узлы графа (идея для редактора)

- **Surface / Material Output** — финальный выход цвета.  
  Входы: *Albedo*, *Normal*, *Roughness*, *Metallic*, *Emissive*, *AO*.
- **Directional Light** — виртуальный узел, читает из `ubo.dirLight*`. Возвращает вклад освещения.
- **Point Lights Accumulate** — *агрегатор*, который разворачивается в цикл по массиву/SSBO.
  - Входы: `normalWS`, `viewDirWS`, `roughness`, `metallic`, `albedo`
  - Параметры: лимит N, тени/IES и т. п.
  - Выходы: `diffuseAccum`, `specularAccum` (или сразу `lightingAccum`).
- **BRDF** — функция/узел, используемая Directional и Accumulate.
- **Ambient / IBL** — окружение и отражения (irradiance + prefilter + BRDF LUT).

---

## 3. Шаблон генерируемого кода

### BRDF
```glsl
struct BRDFResult { vec3 diff; vec3 spec; };

BRDFResult evalBRDF(vec3 N, vec3 V, vec3 L,
                    vec3 baseColor, float roughness, float metallic);
```

### Directional Light
```glsl
vec3 shadeDirectional(vec3 N, vec3 V,
                      vec3 baseColor, float roughness, float metallic) {
    vec3 Ld = normalize(ubo.dirLightDir_Int.xyz);
    float NdotL = max(dot(N, Ld), 0.0);
    if (NdotL <= 0.0) return vec3(0.0);

    BRDFResult r = evalBRDF(N, V, Ld, baseColor, roughness, metallic);
    float I = ubo.dirLightDir_Int.w;
    return (r.diff + r.spec) * ubo.dirLightColor.rgb * I * NdotL;
}
```

### Point Lights Accumulate
```glsl
vec3 shadePoints(vec3 P, vec3 N, vec3 V,
                 vec3 baseColor, float roughness, float metallic) {
    vec3 sum = vec3(0.0);
    int count = min(ubo.numPointLights, 32); // или length(L.pointLights) для SSBO
    for (int i = 0; i < count; ++i) {
        PointLight Lp = L.pointLights[i];

        vec3 Lvec = Lp.position.xyz - P;
        float dist = length(Lvec);
        vec3 Ldir = (dist > 0.0) ? Lvec / dist : vec3(0,0,1);

        float NdotL = max(dot(N, Ldir), 0.0);
        if (NdotL <= 0.0) continue;

        float att = 1.0 / (Lp.attenuation.x
                         + Lp.attenuation.y * dist
                         + Lp.attenuation.z * dist * dist);

        BRDFResult r = evalBRDF(N, V, Ldir, baseColor, roughness, metallic);
        float I = Lp.color.a;
        vec3  C = Lp.color.rgb;

        sum += (r.diff + r.spec) * C * (I * att * NdotL);
    }
    return sum;
}
```

### Сборка в материале
```glsl
vec3 N = normalize(normalWS);
vec3 V = normalize(cameraPosWS - P);
vec3 base = baseColor;

vec3 L_ambient  = ubo.ambient.rgb * base;
vec3 L_dir      = shadeDirectional(N, V, base, roughness, metallic);
vec3 L_points   = shadePoints(P, N, V, base, roughness, metallic);
vec3 L_emissive = emissive;

vec3 color = L_ambient + L_dir + L_points + L_emissive;
```

---

## 4. UX в редакторе узлов

- `Texture → BaseColor → MaterialOutput.Albedo`  
- `NormalMap → TBN → MaterialOutput.Normal`  
- `Slider → Roughness, Metallic`  
- `DirectionalLight → Lighting`  
- `PointLightsAccumulate → Lighting`  
- `Add/Mix → MaterialOutput.ShadedColor`

Художник не видит циклов — их скрывает узел-агрегатор.

---

## 5. Масштабирование и производительность

- **Forward+ / Clustered** — вместо «все огни» → список огней на кластер/тайл.  
- **Лимиты** — N для мобильных.  
- **Мат-варианты** — unlit пропускает освещение.  
- **Тени** — опционально подключаются в агрегаторе.

---

## 6. Когда лучше deferred

Сотни источников → удобнее **deferred**: материал пишет G-buffer, свет считается отдельно.

---

## 7. Детали для генератора

- Стабильные имена (`evalBRDF`, `shadePoints`) → общий include.  
- Фича-флаги: `#define USE_NORMALMAP`, `USE_IBL`, …  
- Валидация типов: `normalWS` в мировом пространстве, `baseColor` — линейный.  
- Интенсивность конвертируйте в движке, в шейдер отдавайте нормализованное.

---

Готов дополнить микро-DSL (YAML) для сериализации узлов и показать, как по YAML собирать GLSL.
