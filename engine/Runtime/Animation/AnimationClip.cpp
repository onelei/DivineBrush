//
// Created by onelei on 2024/5/23.
//

#include "AnimationClip.h"
#include "../Application.h"
#include "fstream"
#include "../../depends/debug/debug.h"
#include "../Time/Time.h"

#define ANIMATION_HEADER "skeleton_anim"
#define ANIMATION_FRAME_RATE 24

namespace DivineBrush {
    AnimationClip::AnimationClip() {

    }

    AnimationClip::~AnimationClip() {

    }

    void AnimationClip::LoadFromFile(const std::string &filePath) {
        std::ifstream fileStream(Application::GetDataPath() + filePath, std::ios::in | std::ios::binary);
        if (!fileStream.is_open()) {
            Debug::LogError("Failed to open file: " + filePath);
            return;
        }
        char fileHeader[14];
        fileStream.read(fileHeader, 13);
        fileHeader[13] = '\0';
        if (strcmp(fileHeader, ANIMATION_HEADER) != 0) {
            Debug::LogError("Invalid animation file: " + filePath);
            return;
        }
        unsigned short nameLength;
        fileStream.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
        char *nameChar = new char[nameLength + 1];
        fileStream.read(nameChar, nameLength);
        nameChar[nameLength] = '\0';
        this->name = nameChar;
        delete[] nameChar;
        fileStream.read(reinterpret_cast<char *>(&frameCount), sizeof(frameCount));
        fileStream.read(reinterpret_cast<char *>(&frameRate), sizeof(frameRate));
        unsigned short boneCount;
        fileStream.read(reinterpret_cast<char *>(&boneCount), sizeof(boneCount));
        for (unsigned short i = 0; i < boneCount; i++) {
            unsigned short boneNameLength;
            fileStream.read(reinterpret_cast<char *>(&boneNameLength), sizeof(boneNameLength));
            char *boneNameChar = new char[boneNameLength + 1];
            fileStream.read(boneNameChar, boneNameLength);
            boneNameChar[boneNameLength] = '\0';
            this->boneNames.emplace_back(boneNameChar);
            delete[] boneNameChar;
        }
        for (unsigned short i = 0; i < frameCount; i++) {
            std::vector<glm::mat4> boneMat4s;
            std::vector<glm::mat3> boneMat3s;
            fileStream.read(reinterpret_cast<char *>(&boneCount), sizeof(boneCount));
            for (unsigned short j = 0; j < boneCount; j++) {
                glm::mat4 boneMat4;
                fileStream.read(reinterpret_cast<char *>(&boneMat4), sizeof(float) * 16);
                boneMat4s.push_back(boneMat4);
                boneMat3s.emplace_back(glm::transpose(glm::inverse(boneMat4)));
            }
            this->boneFrameMat4s.push_back(boneMat4s);
            this->boneFrameNormalMat3s.push_back(boneMat3s);
        }
        fileStream.close();
    }

    std::vector<glm::mat4> &AnimationClip::GetCurrentFrameBoneMat4() {
        return boneFrameMat4s[currentFrame];
    }

    std::vector<glm::mat3> &AnimationClip::GetCurrentFrameNormalBoneMat3() {
        return boneFrameNormalMat3s[currentFrame];
    }

    void AnimationClip::OnUpdate() {
        if (!isPlaying) {
            return;
        }
        auto currentTime = Time::GetTimeSinceStartup() - startTime;
        auto currentFrameIndex = static_cast<unsigned short>(currentTime * ANIMATION_FRAME_RATE);
        currentFrame = currentFrameIndex % frameCount;
    }

    void AnimationClip::Play() {
        this->startTime = Time::GetTimeSinceStartup();
        this->isPlaying = true;
    }

    void AnimationClip::Stop() {
        this->isPlaying = false;
    }
} // DivineBrush