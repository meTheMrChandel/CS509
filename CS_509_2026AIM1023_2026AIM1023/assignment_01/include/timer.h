#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

TimePoint startTimer();
double stopTimer(TimePoint start);

#endif