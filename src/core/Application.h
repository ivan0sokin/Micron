#ifndef _MICRON_APPLICATION_H
#define _MICRON_APPLICATION_H

#include "Logger.h"
#include "Timer.h"

namespace Micron
{
    class Application
    {
    public:
        Application() noexcept = default;
        virtual ~Application() noexcept = 0;

        void Run() noexcept;

        static Rc<Application> GetInstance() noexcept;
    private:
        bool isRunning = true;
    };
}

#endif