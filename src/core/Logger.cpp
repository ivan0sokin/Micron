#include "Logger.h"

namespace Micron
{
    Rc<logger> Logger::internalCoreLogger;
    Rc<logger> Logger::applicationLogger;

    void Logger::Initialize() noexcept
    {
        std::vector<sink_ptr> sinks;
        sinks.emplace_back(MakeRc<sinks::stdout_color_sink_mt>());
        sinks.emplace_back(MakeRc<sinks::basic_file_sink_mt>("Micron.log", true));

        sinks[0]->set_pattern("%^[%d.%m.%Y %T] [%n: %l] %v%$");
        sinks[1]->set_pattern("[%d.%m.%Y %T] [%n: %l] %v");

        internalCoreLogger = MakeRc<logger>("MICRON", sinks.begin(), sinks.end());
        register_logger(internalCoreLogger);

        internalCoreLogger->set_level(level::trace);
        internalCoreLogger->flush_on(level::trace);
    
        applicationLogger = MakeRc<logger>("APPLICATION", sinks.begin(), sinks.end());
        register_logger(applicationLogger);

        applicationLogger->set_level(level::trace);
        applicationLogger->flush_on(level::trace);
    }
}