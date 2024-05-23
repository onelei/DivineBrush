//
// Created by onelei on 2024/5/23.
//

#ifndef ENGINE_ANIMATIONCLIP_H
#define ENGINE_ANIMATIONCLIP_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace DivineBrush {

    class AnimationClip {
    public:
        AnimationClip();

        ~AnimationClip();

        void LoadFromFile(const std::string &filePath);

        std::vector<glm::mat4> &GetCurrentFrameBoneMat4();

        std::vector<glm::mat3> &GetCurrentFrameNormalBoneMat3();

        void OnUpdate();

        void Play();

        void Stop();

    private:
        std::string name;
        unsigned short frameCount;
        unsigned short frameRate;
        std::vector<std::string> boneNames;
        std::vector<std::vector<glm::mat4>> boneFrameMat4s;
        std::vector<std::vector<glm::mat3>> boneFrameNormalMat3s;
        float startTime = 0.0f;
        unsigned short currentFrame = 0;
        bool isPlaying = false;
    };

} // DivineBrush

#endif //ENGINE_ANIMATIONCLIP_H
