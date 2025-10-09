#include "VertexBufferElement.h"

namespace Lada {
    ShaderDataType ShaderDataType::Float {"Float", GpuElementType::FLOAT, 1, 4};
    ShaderDataType ShaderDataType::Float2 {"Float2", GpuElementType::FLOAT,  2, 4 * 2};
    ShaderDataType ShaderDataType::Float3 {"Float3", GpuElementType::FLOAT,  3, 4 * 3};
    ShaderDataType ShaderDataType::Float4 {"Float4", GpuElementType::FLOAT,  4, 4 * 4};

    ShaderDataType ShaderDataType::Matrix3 {"Matrix3", GpuElementType::FLOAT, 3 * 3, 4 * 3 * 3};
    ShaderDataType ShaderDataType::Matrix4 {"Matrix4", GpuElementType::FLOAT, 4 * 4, 4 * 4 * 4};

    ShaderDataType ShaderDataType::Int {"Int", GpuElementType::INT,     1, 4};
    ShaderDataType ShaderDataType::Int2 {"Int2", GpuElementType::INT,    2, 4 * 2};
    ShaderDataType ShaderDataType::Int3 {"Int3", GpuElementType::INT,    3, 4 * 3};
    ShaderDataType ShaderDataType::Int4 {"Int4", GpuElementType::INT,    4, 4 * 4};

    ShaderDataType ShaderDataType::Boolean {"Boolean", GpuElementType::BOOL, 1, 1};
}
