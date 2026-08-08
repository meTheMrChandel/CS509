#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Simplify high-resolution timing types.
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

// Returns current high-resolution timepoint.
TimePoint start_timer();

// Computes elapsed microseconds since t_startTime.
double stop_timer(TimePoint t_startTime);

#endif // TIMER_H
