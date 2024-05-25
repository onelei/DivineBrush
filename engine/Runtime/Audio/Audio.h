//
// Created by onelei on 2024/3/29.
//

#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>
#include "glm/glm.hpp"

namespace DivineBrush {

    class Audio {
    public:

        static void Init();

        static void Play2D(const std::string &filename);

        static void Play3D(const std::string &filename, glm::vec3 pos);

        static void Play(ALuint sfxSource);

        static void Pause(ALuint sfxSource);

        static void Resume(ALuint sfxSource);

        static void Stop(ALuint sfxSource);

        static void Clear(ALuint sfxSource);

        static void ClearAll();

    private:
        static bool isInit;

        static std::vector<char> LoadWAV(const std::string &filename, ALenum &format, ALsizei &freq);

        static void CheckError(const char *operation);
    };

} // DivineBrush

#endif //ENGINE_AUDIO_H

