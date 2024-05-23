//
// Created by onelei on 2024/5/23.
//

#ifndef ENGINE_ANIMATION_H
#define ENGINE_ANIMATION_H

#include "../Component/Component.h"
#include "AnimationClip.h"
#include <unordered_map>

namespace DivineBrush {

    class Animation : public Component {
    public:
        Animation();

        ~Animation();

        void OnUpdate() override;

        void Play(const std::string &name);

        void Stop();

        void LoadFromFile(const std::string &filePath, const std::string &name);

        AnimationClip *GetAnimationClip() const {
            return animationClip;
        }

    private:
        AnimationClip *animationClip = nullptr;
        std::unordered_map<std::string, AnimationClip *> animationClips;
    };

} // DivineBrush

#endif //ENGINE_ANIMATION_H
