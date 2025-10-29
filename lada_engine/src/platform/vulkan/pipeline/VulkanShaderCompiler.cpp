#include "VulkanShaderCompiler.h"

#include <algorithm>


namespace Lada {
    static std::string ToLower(std::string s) {
        std::ranges::transform(s, s.begin(), [](const unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return s;
    }

    VulkanShaderCompiler::VulkanShaderCompiler(const bool enableDebugInfo,
                                               const bool treatWarningsAsErrors)
        : m_EnableDebugInfo(enableDebugInfo), m_TreatWarningsAsErrors(treatWarningsAsErrors) {
    }

    CompileResult VulkanShaderCompiler::CompileString(const std::string &source, const ShaderStage stage,
                                                      const std::string &virtualPath,
                                                      const std::unordered_map<std::string, std::string> &defines)
    const {
        CompileResult out;

        const shaderc::Compiler compiler;
        shaderc::CompileOptions opts;

        opts.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
        opts.SetSourceLanguage(shaderc_source_language_glsl);
        opts.SetOptimizationLevel(shaderc_optimization_level_performance);

        if (m_EnableDebugInfo) {
            opts.SetGenerateDebugInfo();
            opts.SetOptimizationLevel(shaderc_optimization_level_zero);
        }
        if (m_TreatWarningsAsErrors) {
            opts.SetWarningsAsErrors();
        }

        for (const auto &[k, v]: defines) {
            opts.AddMacroDefinition(k, v);
        }

        // Если используешь #include в GLSL — подключи Includer (можно свой класс).
        // opts.SetIncluder(std::make_unique<MyIncluder>(...));

        const auto kind = ToShadercKind(stage);
        const auto result = compiler.CompileGlslToSpv(source.c_str(), source.size(), kind,
                                                      virtualPath.c_str(), "main", opts);

        out.log.assign(result.GetErrorMessage());

        if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
            out.success = false;
            return out;
        }

        out.spirv.assign(result.cbegin(), result.cend());
        out.success = true;
        return out;
    }

    std::optional<ShaderStage> VulkanShaderCompiler::GuessStageFromPath(const std::string &path) {
        const auto p = ToLower(path);
        if (p.ends_with(".vert") || p.ends_with(".vs")) return ShaderStage::Vertex;
        if (p.ends_with(".frag") || p.ends_with(".fs")) return ShaderStage::Fragment;
        if (p.ends_with(".comp") || p.ends_with(".cs")) return ShaderStage::Compute;
        if (p.ends_with(".geom") || p.ends_with(".gs")) return ShaderStage::Geometry;
        if (p.ends_with(".tesc")) return ShaderStage::TessControl;
        if (p.ends_with(".tese")) return ShaderStage::TessEvaluation;
        return std::nullopt;
    }

    shaderc_shader_kind VulkanShaderCompiler::ToShadercKind(const ShaderStage stage) {
        switch (stage) {
            case ShaderStage::Vertex: return shaderc_glsl_vertex_shader;
            case ShaderStage::Fragment: return shaderc_glsl_fragment_shader;
            case ShaderStage::Compute: return shaderc_glsl_compute_shader;
            case ShaderStage::Geometry: return shaderc_glsl_geometry_shader;
            case ShaderStage::TessControl: return shaderc_glsl_tess_control_shader;
            case ShaderStage::TessEvaluation: return shaderc_glsl_tess_evaluation_shader;
        }
        return shaderc_glsl_infer_from_source;
    }
}
