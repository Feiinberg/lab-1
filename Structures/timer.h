
#pragma once
#include <iostream>
#include <chrono>
class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_;
    
public:
    void start() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    long long end() {
        end_ = std::chrono::high_resolution_clock::now();

        long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
        return duration;
    }
};
template<typename T>
void timer(void (*f)(T&), T& list) {
    Timer t;
    t.start();
    f(list);
    std::cout << t.end() << std::endl;
}
