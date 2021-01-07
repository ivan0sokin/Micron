#ifndef _MICRON_CORE_TIMER_H
#define _MICRON_CORE_TIMER_H

#include <chrono>
#include "types/BasicTypes.h"

namespace Micron
{ 
    using TimePoint = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::duration<Float32, std::milli>;

    class Timer
    {
    private:
        inline static TimePoint currentFrameTime, lastFrameTime;
        inline static Duration durationBetweenFrames;
    public:
        inline Timer() = delete;
        inline ~Timer() noexcept = default;
        inline Timer(Timer const &other) = delete;
        inline Timer(Timer &&other) = delete;

        inline static Void Reset() noexcept { lastFrameTime = std::chrono::high_resolution_clock::now(); }
        inline static Void Update() noexcept
        {
            currentFrameTime = std::chrono::high_resolution_clock::now();
            durationBetweenFrames = currentFrameTime - lastFrameTime;

            lastFrameTime = currentFrameTime;
        }
        constexpr static Float32 GetDeltaTime() noexcept { return durationBetweenFrames.count(); }
    };
}

#endif