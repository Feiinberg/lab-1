#include "Timer.h"

void Timer::start() {
    start_ = std::chrono::high_resolution_clock::now();
}

long long Timer::end() {
    end_ = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
    return duration;
}
