#pragma once

#include <iostream>
#include <time.h>
using namespace std;
class timer {
private:
    clock_t _start;
    clock_t _stop;
public:
    timer() :_start(clock()), _stop(clock()) {}
    void start() {
        _start = clock();
    }
    void stop() {
        _stop = clock();
    }
    float duration() {
        return (float(_stop) - float(_start)) / CLOCKS_PER_SEC;
    }
};

template <typename T>
float time_sort_routine(T a[], unsigned int  size,
    void (*f)(T*, unsigned int)) {
    timer t;
    t.start();
    f(a, size);
    t.stop();
    return t.duration();
}