//
// Created by onelei on 2024/5/6.
//

#include "Time.h"

namespace DivineBrush {
    std::chrono::steady_clock::time_point Time::startTime;
    float Time::deltaTime = 0.0f;
    float Time::time = 0.0f;
    float Time::timeSinceStartup = 0.0f;
    float Time::fixDeltaTime = 1.0 / 30;
    float Time::timeScale = 1.0f;

    void Time::Init() {
        startTime = std::chrono::steady_clock::now();
    }

    void Time::Update() {
        auto timeSinceStartupNow = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - startTime).count();
        deltaTime = (timeSinceStartupNow - timeSinceStartup) * timeScale;
        time += deltaTime;
        timeSinceStartup = timeSinceStartupNow;
    }

    float Time::GetDeltaTime() {
        return deltaTime;
    }

    float Time::GetTime() {
        return time;
    }

    float Time::GetTimeSinceStartup() {
        return timeSinceStartup;
    }

    float Time::GetFixDeltaTime() {
        return fixDeltaTime;
    }

    void Time::SetFixDeltaTime(float _fixDeltaTime) {
        fixDeltaTime = _fixDeltaTime;
    }
} // DivineBrush