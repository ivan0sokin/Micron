#ifndef _MICRON_LOGGER_H
#define _MICRON_LOGGER_H

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Micron
{
    class Logger
    {
    public:
        Logger() = delete;
        Logger(Logger const &other) = delete;
        Logger(Logger &&other) = delete;
        ~Logger() = delete;

        static void Initialize() noexcept;

        static inline Rc<spdlog::logger> & GetInternalCoreLogger() noexcept { return internalCoreLogger; }
        static inline Rc<spdlog::logger> & GetApplicationLogger() noexcept { return applicationLogger; }
    private:
        static Rc<spdlog::logger> internalCoreLogger;
        static Rc<spdlog::logger> applicationLogger;
    };
}

#define _MICRON_CORE_LOG_TRACE(...) ::Micron::Logger::GetInternalCoreLogger()->trace(__VA_ARGS__)
#define _MICRON_CORE_LOG_INFO(...) ::Micron::Logger::GetInternalCoreLogger()->info(__VA_ARGS__)
#define _MICRON_CORE_LOG_WARN(...) ::Micron::Logger::GetInternalCoreLogger()->warn(__VA_ARGS__)
#define _MICRON_CORE_LOG_ERROR(...) ::Micron::Logger::GetInternalCoreLogger()->error(__VA_ARGS__)
#define _MICRON_CORE_LOG_CRITICAL(...) ::Micron::Logger::GetInternalCoreLogger()->critical(__VA_ARGS__)

#define MICRON_LOG_TRACE(...) ::Micron::Logger::GetApplicationLogger()->trace(__VA_ARGS__)
#define MICRON_LOG_INFO(...) ::Micron::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define MICRON_LOG_WARN(...) ::Micron::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define MICRON_LOG_ERROR(...) ::Micron::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define MICRON_LOG_CRITICAL(...) ::Micron::Logger::GetApplicationLogger()->critical(__VA_ARGS__)

#ifdef MICRON_DEBUG
    #define _MICRON_CORE_LOG_DEBUG(...) ::Micron::Logger::GetInternalCoreLogger()->debug(__VA_ARGS__)
    #define MICRON_LOG_DEBUG(...) ::Micron::Logger::GetApplicationLogger()->debug(__VA_ARGS__)
#else
    #define _MICRON_CORE_LOG_DEBUG(...)
    #define MICRON_LOG_DEBUG(...)
#endif

#endif