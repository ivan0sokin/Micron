#ifndef _MICRON_ENGINE_CORE_TIME_TIMER_HPP
#define _MICRON_ENGINE_CORE_TIME_TIMER_HPP

#include <chrono>
#include "../types/BasicTypes.h"

namespace Micron
{ 
    using TimePoint = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::duration<Float32, std::milli>;
    
    class Timer
    {
    public:
        inline Timer() noexcept = default;
        inline ~Timer() noexcept = default;

        inline Void Reset() noexcept { lastFrameTime = std::chrono::high_resolution_clock::now(); }
        inline Void Update() noexcept
        {
            currentFrameTime = std::chrono::high_resolution_clock::now();
            durationBetweenFrames = currentFrameTime - lastFrameTime;

            lastFrameTime = currentFrameTime;
        }
        constexpr Float32 GetDeltaTime() noexcept { return durationBetweenFrames.count(); }
    private:
        TimePoint currentFrameTime, lastFrameTime;
        Duration durationBetweenFrames;
    };
}

#endif