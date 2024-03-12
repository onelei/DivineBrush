//
// Created by onelei on 2024/3/11.
//

#ifndef ENGINE_STOP_WATCH_H
#define ENGINE_STOP_WATCH_H

#include <chrono>
#include <iostream>

class StopWatch {
public:
    StopWatch() {
        Start();
    }

    void Start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void Stop() {
        endTime = std::chrono::high_resolution_clock::now();
    }

    void Restart() {
        Start();
    }

    int ElapsedSeconds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    }

    long ElapsedMilliSeconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
};

#endif //ENGINE_STOP_WATCH_H
