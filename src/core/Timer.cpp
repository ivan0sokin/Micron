#include "Timer.h"

namespace Micron
{
    TimePoint Timer::currentFrameTime, Timer::lastFrameTime;
    duration<double, std::milli> Timer::durationBetweenFrames;

    void Timer::Reset() noexcept
    {
        lastFrameTime = high_resolution_clock::now();
    }

    void Timer::Update() noexcept
    {
        currentFrameTime = high_resolution_clock::now();
        durationBetweenFrames = currentFrameTime - lastFrameTime;
        
        lastFrameTime = currentFrameTime;
    }
}