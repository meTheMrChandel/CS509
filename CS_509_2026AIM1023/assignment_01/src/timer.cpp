#include "../include/timer.h"

// Capture current system high-resolution clock time point.
TimePoint start_timer()
{
    return Clock::now();
}

// Compute difference between now and t_start timepoint in milliseconds.
double stop_timer(TimePoint t_start)
{
    TimePoint t_end = Clock::now();
    return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
