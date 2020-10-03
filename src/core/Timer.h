#ifndef _MICRON_TIMER_H
#define _MICRON_TIMER_H

#include <chrono>

namespace Micron
{ 
    using namespace std::chrono;
    using TimePoint = high_resolution_clock::time_point;

    class Timer
    {
    public:
        Timer() = delete;
        ~Timer() = delete;
        Timer(Timer const &other) = delete;
        Timer(Timer &&other) = delete;

        static void Reset() noexcept;
        static void Update() noexcept;
        static constexpr double GetDeltaTime() noexcept { return durationBetweenFrames.count(); }
    private:
        static TimePoint currentFrameTime, lastFrameTime;
        static duration<double, std::milli> durationBetweenFrames;
    };
}

#endif