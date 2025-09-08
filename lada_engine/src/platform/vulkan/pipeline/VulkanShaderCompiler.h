#pragma once

#include <shaderc/shaderc.hpp>

namespace Lada {

    // TODO: Кэширование: по хэшу source + options + stage
    //       (std::unordered_map или файловый кэш .spv рядом) — ускорит hot-reload.

    // TODO: Пре-процессинг: использовать compiler.PreprocessGlsl(...)
    //       для логгинга после #include/#define.

    // TODO: Поддержка HLSL:
    //       opts.SetSourceLanguage(shaderc_source_language_hlsl)
    //       + соответствующий shaderc_shader_kind.

    // TODO: SPIR-V оптимизация: после компиляции прогонять spirv-opt
    //       (через SPIRV-Tools API) — inline, DCE, unroll.

    // TODO: Рефлексия: использовать SPIRV-Cross для извлечения биндингов,
    //       лэйаутов, входов/выходов (для автогенерации pipeline layouts).

    // TODO: Diagnostics policy: сделать уровни строгости конфигурируемыми
    //       (Editor/CI включают Werror, Runtime — мягче).

    // TODO: Новые сигнатуры: перегрузка CompileFile(path, stage) —
    //       читать файл, угадывать стадию по расширению и вызывать CompileString.

    enum class ShaderStage {
        Vertex, Fragment, Compute, Geometry, TessControl, TessEval
    };

    struct CompileResult {
        bool success = false;
        std::vector<uint32_t> spirv;
        std::string log;
    };

    class VulkanShaderCompiler {
    public:
        explicit VulkanShaderCompiler(bool enableDebugInfo = false, bool treatWarningsAsErrors = false);

        [[nodiscard]] CompileResult CompileString(const std::string &source, ShaderStage stage,
                                    const std::string &virtualPath = "shader.glsl",
                                    const std::unordered_map<std::string, std::string> &defines = {}) const;
        static std::optional<ShaderStage> GuessStageFromPath(const std::string& path);

    private:
        static shaderc_shader_kind ToShadercKind(ShaderStage stage);
        bool m_EnableDebugInfo = false;
        bool m_TreatWarningsAsErrors = false;
    };
}
