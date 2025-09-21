#pragma once
#include <optional>
#include <unordered_map>

namespace Svch {
    enum class BaseKind { Bool, Int, UInt, Float, Double };

    enum class TypeKind { Scalar, Vector, Matrix };

    struct Type {
        TypeKind kind;
        BaseKind base;
        unsigned int rows; // =1 для скаляра и вектора; матрица: rows>=2
        unsigned int cols; // =1 для скаляра; вектор: cols=components; матрица: cols>=2

        bool isScalar() const {
            return kind == TypeKind::Scalar;
        }

        bool isVector() const {
            return kind == TypeKind::Vector;
        }
        bool isMatrix() const {
            return kind == TypeKind::Matrix;
        }

        unsigned int components() const { return isVector() ? cols : 1; }

        static Type Scalar(const BaseKind kind) {
            return {TypeKind::Scalar, kind, 1, 1};
        }

        static Type Vector(const BaseKind kind, const unsigned int components) {
            return {TypeKind::Vector, kind, 1, components};
        }

        static Type Matrix(const BaseKind kind, const unsigned int rows, const unsigned int columns) {
            return { TypeKind::Matrix,kind, rows, columns };
        }
    };

    BaseKind Promote(const BaseKind a, const BaseKind b) {
        if (a == b) return a;
        auto rank = [](const BaseKind k){
            switch (k) { case BaseKind::Double: return 4;
                case BaseKind::Float:  return 3;
                case BaseKind::UInt:   return 2;
                case BaseKind::Int:    return 1;
                default:               return 0; }
        };
        return (rank(a) >= rank(b)) ? a : b;
    }

    enum class BinOp { Add, Sub, Mul, Div };

    struct OpRule {
        std::optional<Type> (*infer)(const Type&, const Type&);
    };

    struct OpRegistry {
        std::unordered_map<BinOp, OpRule> rules;

        const OpRule* get(const BinOp op) const {
            const auto it = rules.find(op);
            return it == rules.end() ? nullptr : &it->second;
        }
    };

    bool isArithmeticBase(const BaseKind b) {
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
}
