// #include "Timer.h"

// Timer::Timer() : timeLimit(0), running(false) {}

// void Timer::setTimeLimit(int seconds) {
//     timeLimit = seconds;
// }

// void Timer::startTimer() {
//     startTime = std::chrono::steady_clock::now();
//     running = true;
// }

// void Timer::stopTimer() {
//     running = false;
// }

// bool Timer::isTimeExceeded() const {
//     if (!running) {
//         return false;
//     }
//     auto currentTime = std::chrono::steady_clock::now();
//     auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
//     return elapsedSeconds > timeLimit;
// }
