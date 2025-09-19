# Архитектура типов и операций GLSL (+, −, ×, ÷)

## 1. Базовые сущности

~~~cpp
enum class BaseKind { Bool, Int, UInt, Float, Double };

enum class TypeKind { Scalar, Vector, Matrix };

struct Type {
    TypeKind   kind;
    BaseKind   base;      // компонентный тип
    uint16_t   rows;      // =1 для скаляра и вектора; матрица: rows>=2
    uint16_t   cols;      // =1 для скаляра; вектор: cols=components; матрица: cols>=2

    bool isScalar() const { return kind == TypeKind::Scalar; }
    bool isVector() const { return kind == TypeKind::Vector; }
    bool isMatrix() const { return kind == TypeKind::Matrix; }

    uint16_t components() const { return isVector() ? cols : 1; }

    static Type Scalar(BaseKind b)                { return {TypeKind::Scalar, b, 1, 1}; }
    static Type Vector(BaseKind b, uint16_t n)    { return {TypeKind::Vector, b, 1, n}; }
    static Type Matrix(BaseKind b, uint16_t r, uint16_t c)
                                                  { return {TypeKind::Matrix, b, r, c}; }
};
~~~

---

## 2. Приведение типов

~~~cpp
BaseKind Promote(BaseKind a, BaseKind b) {
    if (a == b) return a;
    auto rank = [](BaseKind k){
        switch (k) { case BaseKind::Double: return 4;
                     case BaseKind::Float:  return 3;
                     case BaseKind::UInt:   return 2;
                     case BaseKind::Int:    return 1;
                     default:               return 0; }
    };
    return (rank(a) >= rank(b)) ? a : b;
}
~~~

---

## 3. Каталог операций

~~~cpp
enum class BinOp { Add, Sub, Mul, Div };

struct OpRule {
    std::optional<Type> (*infer)(const Type&, const Type&);
};

struct OpRegistry {
    std::unordered_map<BinOp, OpRule> rules;
    const OpRule* get(BinOp op) const { 
        auto it = rules.find(op);
        return it == rules.end() ? nullptr : &it->second;
    }
};
~~~

### Вспомогательные проверки

~~~cpp
bool isArithmeticBase(BaseKind b) {
    return b == BaseKind::Int || b == BaseKind::UInt
        || b == BaseKind::Float || b == BaseKind::Double;
}

bool sameShape(const Type& a, const Type& b) {
    if (a.kind != b.kind) return false;
    if (a.isScalar() && b.isScalar()) return true;
    if (a.isVector() && b.isVector()) return a.components() == b.components();
    if (a.isMatrix() && b.isMatrix()) return a.rows == b.rows && a.cols == b.cols;
    return false;
}
~~~

---

## 4. Семантика операций

### `+` и `-`
- `scalar ⊕ scalar` → `scalar(promote)`
- `vector ⊕ vector` (N=N) → `vector(promote, N)`
- `matrix ⊕ matrix` (R×C = R×C) → `matrix(promote, R×C)`
- `scalar ⊕ vector|matrix` → **broadcast** в форму второго операнда

### `*`
- `scalar * X` → `X` (покомпонентно)
- `vector * vector` (N=N) → `vector` (покомпонентно)
- `matrix * matrix` `(R×C) * (C×K)` → `matrix(R×K)` (линейная алгебра)
- `matrix * vector` `(R×C) * (C)` → `vector(R)`
- `vector * matrix` `(1×N) * (N×M)` → `vector(M)`

### `/`
- `X / scalar` → `X` (покомпонентно)
- `scalar / X` → **broadcast** формы `X`
- `vector / vector` (N=N) → `vector` (покомпонентно)
- `matrix / matrix`, `vector / matrix`, `matrix / vector` → ❌ запрещено

---

## 5. Примеры

- `vec3(float) * float` → `vec3(float)`
- `mat4(float) * vec4(float)` → `vec4(float)`
- `mat3x2(float) * mat2x4(float)` → `mat3x4(float)`
- `vec3(float) + vec3(double)` → `vec3(double)` (promotion)
- `vec3 + vec4` → ❌ ошибка (не совпадает размерность)
- `mat4 / mat4` → ❌ ошибка
- `int + float` → `float` (promotion)

---

## 6. Почему это удобно

- Унифицированная модель `(rows, cols)` покрывает скаляры, векторы и матрицы.
- Централизованное приведение компонентных типов через `Promote`.
- `std::optional` у результата — удобно сигнализировать ошибки в нод-редакторе.
- Расширяемость через `OpRegistry`: легко добавить `dot`, `cross`, `transpose`, `length`, `normalize` и т. д.