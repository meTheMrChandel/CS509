#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

// Start the timer
TimePoint startTimer();

// Stop the timer and return elapsed time in milliseconds
double stopTimer(TimePoint start);

#endif