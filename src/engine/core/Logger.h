#ifndef _MICRON_CORE_LOGGER_H
#define _MICRON_CORE_LOGGER_H

#include "Base.h"
#include "types/BasicTypes.h"

#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Micron
{
    class Logger
    {
    public:
        inline Logger(MultibyteStringView name) noexcept
        {
            using namespace spdlog;
            
            auto consoleSink = MakeRc<sinks::stdout_color_sink_mt>();
            auto fileSink = MakeRc<sinks::basic_file_sink_mt>("Micron.log", true);

            consoleSink->set_pattern("%^[%d.%m.%Y %T] [%n: %l] %v%$");
            fileSink->set_pattern("[%d.%m.%Y %T] [%n: %l] %v");

            internalLogger = MakeRc<logger>(name.data(), sinks_init_list{ consoleSink, fileSink });
            register_logger(internalLogger);

            internalLogger->set_level(level::trace);
            internalLogger->flush_on(level::trace);
        }

        template <typename ...Args> constexpr Void Trace(Args &&...args) noexcept { internalLogger->trace(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Debug(Args &&...args) noexcept { internalLogger->debug(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Info(Args &&...args) noexcept { internalLogger->info(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Warn(Args &&...args) noexcept { internalLogger->warn(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Error(Args &&...args) noexcept { internalLogger->error(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Critical(Args &&...args) noexcept { internalLogger->critical(std::forward<Args>(args)...); }

        inline Logger() noexcept = default;
        inline ~Logger() noexcept = default;
    private:
        Rc<spdlog::logger> internalLogger;
    };

    class CoreLogger
    {
    public:
        template <typename ...Args> constexpr static Void Trace(Args &&...args) noexcept { logger.Trace(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr static Void Debug(Args &&...args) noexcept { logger.Debug(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr static Void Info(Args &&...args) noexcept { logger.Info(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr static Void Warn(Args &&...args) noexcept { logger.Warn(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr static Void Error(Args &&...args) noexcept { logger.Error(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr static Void Critical(Args &&...args) noexcept { logger.Critical(std::forward<Args>(args)...); }

        constexpr static MultibyteStringView Name() noexcept { return "MICRON"; }
    private:
        inline static Logger logger = Logger(CoreLogger::Name());
    };
}

#if defined(_MICRON_DEBUG)
    #define _MICRON_DEBUG_LOG(...) CoreLogger::Debug(__VA_ARGS__)
#else
    #define _MICRON_DEBUG_LOG(...)
#endif

#endif