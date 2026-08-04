#include "../include/timer.h"

TimePoint startTimer()
{
    return Clock::now();
}

double stopTimer(TimePoint start)
{
    TimePoint end = Clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}