//
// Created by onelei on 2024/5/23.
//

#include "Animation.h"
#include "rttr/registration.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    RTTR_REGISTRATION {
        rttr::registration::class_<Animation>("Animation")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Animation::Animation() {

    }

    Animation::~Animation() {
        for (auto clip: animationClips) {
            delete clip.second;
        }
    }

    void Animation::OnUpdate() {
        Component::OnUpdate();
        if (animationClip != nullptr) {
            animationClip->OnUpdate();
        }
    }

    void Animation::Play(const std::string &name) {
        if (animationClips.find(name) == animationClips.end()) {
            Debug::LogError("Animation clip not found" + name);
            return;
        }
        animationClip = animationClips[name];
        animationClip->Play();
    }

    void Animation::Stop() {
        if (animationClip != nullptr) {
            animationClip->Stop();
        }
    }

    void Animation::LoadFromFile(const std::string &filePath, const std::string &name) {
        auto newAnimationClip = new AnimationClip();
        newAnimationClip->LoadFromFile(filePath);
        animationClips[name] = newAnimationClip;
    }

} // DivineBrush