#ifndef _MICRON_APPLICATION_H
#define _MICRON_APPLICATION_H

#include "Exceptions.h"
#include "Logger.h"
#include "Timer.h"

namespace Micron
{
    class Application
    {
    public:
        virtual void Initialize() noexcept = 0;
        virtual void OnUpdate(double deltaTime) noexcept = 0;

        static Rc<Application> Instance() noexcept;
    };
}

#endif