#include "timer.h"

template<typename T>
void timer(void (*f)(T&), T& list) {
    Timer t;
    t.start();
    f(list);
    std::cout << t.end() << std::endl;
}


