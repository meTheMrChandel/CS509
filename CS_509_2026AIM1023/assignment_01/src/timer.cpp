#include "../include/timer.h"

TimePoint startTimer() {
    return Clock::now();
}

double stopTimer(TimePoint start) {
    auto end = Clock::now();

    return std::chrono::duration<double, std::micro>(end - start).count();
    //return std::chrono::duration<double, std::milli>(end - start).count();
}