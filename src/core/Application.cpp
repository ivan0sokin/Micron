#include "Application.h"

namespace Micron
{
    void Application::Run() noexcept
    {
        Timer::Reset();
        while(isRunning)
        {
            Timer::Update();
        }
    }
}