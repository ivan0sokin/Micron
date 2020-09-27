#ifndef _MICRON_ENTRYPOINT_H
#define _MICRON_ENTRYPOINT_H

#include "core/Application.h"

#include <fmt/format.h>

int main(int argc, char **argv)
{
    Micron::Logger::Initialize();
    _MICRON_CORE_LOG_INFO
    (
        fmt::format
        (
            "Current Micron version: {}.{}.{}", 
            MICRON_VERSION_MAJOR, MICRON_VERSION_MINOR, MICRON_VERSION_PATCH
        )
    );

    auto application = Micron::Application::Instance();
    application->Initialize();
    
    Micron::Timer::Reset();
    while (true)
    {
        Micron::Timer::Update();
        application->OnUpdate(Micron::Timer::DeltaTime());
    }

    return 0;
}

#endif