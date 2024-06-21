#ifndef TIMER_H
#define TIMER_H

#include <chrono> 

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    int timeLimit; 
    bool running; 

public:
    Timer();

    void setTimeLimit(int seconds);
    void startTimer();
    void stopTimer();
    bool isTimeExceeded() const;
};

#endif
