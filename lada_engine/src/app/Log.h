#pragma once

#include <memory>
#include "spdlog/spdlog.h"

namespace lada::log {
    class Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define LD_CORE_TRACE(...) lada::log::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LD_CORE_DEBUG(...) lada::log::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define LD_CORE_INFO(...) lada::log::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LD_CORE_WARN(...) lada::log::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LD_CORE_ERROR(...) lada::log::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LD_CORE_CRITICAL(...) lada::log::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LD_TRACE(...) lada::log::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LD_DEBUG(...) lada::log::Log::GetClientLogger()->debug(__VA_ARGS__)
#define LD_INFO(...) lada::log::Log::GetClientLogger()->info(__VA_ARGS__)
#define LD_WARN(...) lada::log::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LD_ERROR(...) lada::log::Log::GetClientLogger()->error(__VA_ARGS__)
#define LD_CRITICAL(...) lada::log::Log::GetClientLogger()->critical(__VA_ARGS__)
