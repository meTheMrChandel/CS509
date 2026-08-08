#include "../include/timer.h"

// Capture current system high-resolution clock time point.
TimePoint start_timer()
{
    return Clock::now();
}

// Compute difference between now and t_startTime timepoint in microseconds.
double stop_timer(TimePoint t_startTime)
{
    TimePoint t_endTime = Clock::now();
    return std::chrono::duration<double, std::micro>(t_endTime - t_startTime).count();
}
