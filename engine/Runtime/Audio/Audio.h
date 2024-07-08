//
// Created by onelei on 2024/3/29.
//

#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <condition_variable>
#include "glm/glm.hpp"
#include "AudioSource.h"

namespace DivineBrush {

    class Audio {
    public:

        static void Init();

        static void Update();

        static void AddAudioSource(AudioSource *source);

        static void RemoveAudioSource(AudioSource *source);

        static void Destroy();

    private:
        static std::unordered_set<AudioSource *> sources;
        static std::thread audioThread;
        static std::mutex mutex;
        static bool exitFlag;
        static ALCdevice *device;
        static ALCcontext *context;

        static std::vector<char> LoadWAV(const std::string &filename, ALenum &format, ALsizei &freq);
    };

} // DivineBrush

#endif //ENGINE_AUDIO_H

