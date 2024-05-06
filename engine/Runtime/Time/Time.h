//
// Created by onelei on 2024/5/6.
//

#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

#include <chrono>

namespace DivineBrush {

    class Time {
    public:

        static void Init();

        static void Update();

        static float GetDeltaTime();

        static float GetTime();

        static float GetTimeSinceStartup();

        static float GetFixDeltaTime();

        static void SetFixDeltaTime(float fixDeltaTime);

    private:
        static std::chrono::steady_clock::time_point startTime;
        static float deltaTime;
        static float time;
        static float timeSinceStartup;
        static float fixDeltaTime;
        static float timeScale;
    };

} // DivineBrush

#endif //ENGINE_TIME_H
