#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

// Start Timer for Algo to run
TimePoint startTimer();

// Stop Timer for Algo to stop
double stopTimer(TimePoint start);

#endif