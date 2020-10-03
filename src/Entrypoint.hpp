#ifndef _MICRON_ENTRYPOINT_H
#define _MICRON_ENTRYPOINT_H

#include "core/Application.h"

int main(int argc, char **argv)
{
    Micron::Logger::Initialize();
    _MICRON_CORE_LOG_INFO
    (
        "Current Micron version: {}.{}.{}", 
        MICRON_VERSION_MAJOR, MICRON_VERSION_MINOR, MICRON_VERSION_PATCH
    );
    _MICRON_CORE_LOG_INFO
    (
        "Current platform: {}",
        MICRON_PLATOFRM_STRING
    );

    auto application = Micron::Application::GetInstance();
    application->Run();

    return 0;
}

#endif