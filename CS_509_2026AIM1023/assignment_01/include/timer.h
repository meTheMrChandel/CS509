#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Simplify high-resolution timing types.
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

// Returns current high-resolution timepoint.
TimePoint start_timer();

// Computes elapsed milliseconds since t_start.
double stop_timer(TimePoint t_start);

#endif // TIMER_H
