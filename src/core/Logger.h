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
        inline Logger(String name) noexcept
        {
            using namespace spdlog;

            auto consoleSink = MakeRc<sinks::stdout_color_sink_mt>();
            auto fileSink = MakeRc<sinks::basic_file_sink_mt>("Micron.log", true);

            consoleSink->set_pattern("%^[%d.%m.%Y %T] [%n: %l] %v%$");
            fileSink->set_pattern("[%d.%m.%Y %T] [%n: %l] %v");

            internalLogger = MakeRc<logger>(name, sinks_init_list{ consoleSink, fileSink });
            register_logger(internalLogger);

            internalLogger->set_level(level::trace);
            internalLogger->flush_on(level::trace);
        }

        inline Logger() = delete;
        inline Logger(Logger const &other) = delete;
        inline Logger(Logger &&other) = delete;
        inline  ~Logger() noexcept = default;

        template <typename ...Args> constexpr Void Trace(Args &&...args) noexcept { internalLogger->trace(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Debug(Args &&...args) noexcept { internalLogger->debug(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Info(Args &&...args) noexcept { internalLogger->info(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Warn(Args &&...args) noexcept { internalLogger->warn(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Error(Args &&...args) noexcept { internalLogger->error(std::forward<Args>(args)...); }
        template <typename ...Args> constexpr Void Critical(Args &&...args) noexcept { internalLogger->critical(std::forward<Args>(args)...); }
    private:
        Rc<spdlog::logger> internalLogger;
    };

    inline static Rc<Logger> CoreLogger;
}

#if defined(MICRON_DEBUG)
    #define LOGGER_DEBUG(logger, ...) logger->Debug(__VA_ARGS__)
#else
    #define LOGGER_DEBUG(logger, ...)
#endif

#endif