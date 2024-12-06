#pragma once

#include <iostream>
#include <chrono>

class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_;

public:
    void start();
    long long end();
};

template<typename T>
void timer(void (*f)(T&), T& list);

#include "timer.tpp"