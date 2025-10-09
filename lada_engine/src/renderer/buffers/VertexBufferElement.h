#pragma once

#include <string>

namespace Lada {
    enum class GpuElementType {
        FLOAT, INT, BOOL
    };

    struct ShaderDataType {
        std::string Name;
        uint32_t ComponentCount;
        uint32_t Size;
        GpuElementType Type;

        ShaderDataType(const std::string &name, const GpuElementType type, const uint32_t componentCount, const uint32_t size)
            : Name(name), ComponentCount(componentCount), Size(size), Type(type) {
        }

        static ShaderDataType Float;
        static ShaderDataType Float2;
        static ShaderDataType Float3;
        static ShaderDataType Float4;

        static ShaderDataType Matrix3;
        static ShaderDataType Matrix4;

        static ShaderDataType Int;
        static ShaderDataType Int2;
        static ShaderDataType Int3;
        static ShaderDataType Int4;

        static ShaderDataType Boolean;
    };

    struct VertexBufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        VertexBufferElement() = delete;

        VertexBufferElement(const ShaderDataType &type, const std::string& name, const bool normalized = false)
            : Name(name), Type(type), Size(type.Size), Offset(0), Normalized(normalized) {}
    };
}
