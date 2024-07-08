//
// Created by onelei on 2024/7/8.
//

#include <al.h>
#include "AudioListener.h"
#include "../Component/GameObject.h"

namespace DivineBrush {
    RTTR_REGISTRATION {
        rttr::registration::class_<AudioListener>("AudioListener")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    AudioListener::AudioListener() {

    }

    AudioListener::~AudioListener() {

    }

    void AudioListener::OnAwake() {
        Component::OnAwake();
        // Set default listener properties
        auto position = GetGameObject()->GetTransform()->GetPosition();
        lastPosition = position;
        alListener3f(AL_POSITION, position.x, position.y, position.z);
        alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        ALfloat orientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
        alListenerfv(AL_ORIENTATION, orientation);
    }

    void AudioListener::OnUpdate() {
        Component::OnUpdate();
        auto position = GetGameObject()->GetTransform()->GetPosition();
        if (lastPosition != position) {
            lastPosition = position;
            alListener3f(AL_POSITION, position.x, position.y, position.z);
        }
    }

} // DivineBrush