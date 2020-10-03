#include "Logger.h"

namespace Micron
{
    using namespace spdlog;

    Rc<logger> Logger::internalCoreLogger;
    Rc<logger> Logger::applicationLogger;

    void Logger::Initialize() noexcept
    {
        auto consoleSink = MakeRc<sinks::stdout_color_sink_mt>();
        auto fileSink = MakeRc<sinks::basic_file_sink_mt>("Micron.log", true);

        consoleSink->set_pattern("%^[%d.%m.%Y %T] [%n: %l] %v%$");
        fileSink->set_pattern("[%d.%m.%Y %T] [%n: %l] %v");
        
        internalCoreLogger = MakeRc<logger>("MICRON", sinks_init_list{ consoleSink, fileSink });
        register_logger(internalCoreLogger);

        internalCoreLogger->set_level(level::trace);
        internalCoreLogger->flush_on(level::trace);
    
        applicationLogger = MakeRc<logger>("APPLICATION", sinks_init_list{ consoleSink, fileSink });
        register_logger(applicationLogger);

        applicationLogger->set_level(level::trace);
        applicationLogger->flush_on(level::trace);
    }
}