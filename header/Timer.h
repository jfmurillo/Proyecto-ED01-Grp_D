#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <thread>
#include <cstdlib>
#include <unordered_map>
#include <queue>
using std::queue;
using std::list;
using std::string;
using std::vector;

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    int timeLimitSeconds;
    bool running;

public:
    Timer();

    void setTimeLimit(int seconds);
    void startTimer();
    void stopTimer();
    bool isTimeExceeded();
    double getElapsedTime() const;
};

#endif
