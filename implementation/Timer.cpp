#include "Timer.h"

Timer::Timer() : timeLimitSeconds(0), running(false) {}

void Timer::setTimeLimit(int seconds) {
    timeLimitSeconds = seconds;
}

void Timer::startTimer() {
    startTime = std::chrono::steady_clock::now();
    running = true;
}

void Timer::stopTimer() {
    endTime = std::chrono::steady_clock::now();
    running = false;
}

bool Timer::isTimeExceeded() {
    if (running) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
        return elapsedSeconds.count() > timeLimitSeconds;
    } else {
        std::chrono::duration<double> elapsedSeconds = endTime - startTime;
        return elapsedSeconds.count() > timeLimitSeconds;
    }
}

double Timer::getElapsedTime() const {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
    return elapsedSeconds.count();
}
