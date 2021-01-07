#ifndef _MICRON_CORE_ENTRYPOINT_H
#define _MICRON_CORE_ENTRYPOINT_H

#include "Application.h"

int main(int argc, char **argv)
{
    auto application = Micron::Application::GetInstance();
    application->StartUp();

    return 0;
}

#endif