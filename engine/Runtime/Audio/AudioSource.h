//
// Created by onelei on 2024/7/8.
//

#ifndef ENGINE_AUDIOSOURCE_H
#define ENGINE_AUDIOSOURCE_H

#include <string>
#include <al.h>
#include <glm/glm.hpp>
#include "AudioClip.h"
#include "../Component/Component.h"

namespace DivineBrush {

    class AudioSource : public Component {
    public:
        AudioSource();

        ~AudioSource();

        void SetClip(AudioClip *clip);

        void Play();

        void Stop();

        void Pause();

        void Resume();

        void OnAwake() override;

        void OnStart() override;

        void OnUpdate() override;

        void OnThreadUpdate();

    private:
        AudioClip *audioClip = nullptr;
        ALuint source = 0;
        ALuint buffer = 0;
        glm::vec3 lastPosition = glm::vec3(0);
        float gain = 1.0f;
        float pitch = 1.0f;
        bool loop = false;
        bool isStopped = false;
    RTTR_ENABLE(Component);
    };

} // DivineBrush

#endif //ENGINE_AUDIOSOURCE_H
