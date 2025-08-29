#pragma once

#include <memory>
#include "spdlog/spdlog.h"

namespace Lada::Log {
    class Logger {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define LD_CORE_TRACE(...) Lada::Log::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LD_CORE_DEBUG(...) Lada::Log::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define LD_CORE_INFO(...) Lada::Log::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LD_CORE_WARN(...) Lada::Log::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LD_CORE_ERROR(...) Lada::Log::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LD_CORE_CRITICAL(...) Lada::Log::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define LD_TRACE(...) Lada::Log::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LD_DEBUG(...) Lada::Log::Logger::GetClientLogger()->debug(__VA_ARGS__)
#define LD_INFO(...) Lada::Log::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LD_WARN(...) Lada::Log::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LD_ERROR(...) Lada::Log::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LD_CRITICAL(...) Lada::Log::Logger::GetClientLogger()->critical(__VA_ARGS__)

#define LD_CORE_ASSERT_WITH_ERROR(condition, ...) \
if (!(condition)) { \
    LD_CORE_ERROR(__VA_ARGS__); \
    std::abort(); \
}

#define LD_VK_ASSERT_SUCCESS(expr, ...) \
if (expr != VK_SUCCESS) { \
    LD_CORE_ERROR(__VA_ARGS__); \
    std::abort(); \
}
