//
// Created by onelei on 2024/5/23.
//

#include <filesystem>
#include <fstream>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "AnimationClip.h"
#include "../Application.h"
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

    int AnimationClip::getBoneIndex(const std::string &boneName) const {
        auto it = std::find(boneNames.begin(), boneNames.end(), boneName);
        if (it != boneNames.end()) {
            return std::distance(boneNames.begin(), it);
        }
        return -1;
    }

    std::string AnimationClip::ReplaceChar(std::string fileName, char oldChar, char newChar) const {
        if (fileName.find(oldChar) != std::string::npos) {
            std::replace(fileName.begin(), fileName.end(), oldChar, newChar);
        }
        return fileName;
    }

    void AnimationClip::Write(std::string filePath) const {
        // 路径转小写
        std::transform(filePath.begin(), filePath.end(), filePath.begin(), ::tolower);
        std::filesystem::path path(filePath);
        std::string fileName = path.filename().string();
        fileName = ReplaceChar(fileName, ' ', '_');
        fileName = ReplaceChar(fileName, '|', '_');
        path.replace_filename(fileName);

        if (!std::filesystem::exists(path.parent_path())) {
            std::filesystem::create_directories(path.parent_path());
        }

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            Debug::LogError("Failed to open file: " + filePath);
            return;
        }

        std::string type = "skeleton_anim";
        file.write(type.c_str(), type.size());

        unsigned short nameLen = name.size();
        file.write(reinterpret_cast<const char *>(&nameLen), sizeof(nameLen));
        file.write(name.c_str(), name.size());

        file.write(reinterpret_cast<const char *>(&frameCount), sizeof(frameCount));
        file.write(reinterpret_cast<const char *>(&frameRate), sizeof(frameRate));

        unsigned short boneNum = boneNames.size();
        file.write(reinterpret_cast<const char *>(&boneNum), sizeof(boneNum));

        for (const auto &boneName: boneNames) {
            unsigned short boneNameLen = boneName.size();
            file.write(reinterpret_cast<const char *>(&boneNameLen), sizeof(boneNameLen));
            file.write(boneName.c_str(), boneName.size());
        }

        for (const auto &frame: boneFrameMat4s) {
            for (const auto &boneMatrix: frame) {
                file.write(reinterpret_cast<const char *>(&boneMatrix), sizeof(glm::mat4));
            }
        }

        file.close();
    }

    void AnimationClip::ExportSkeletonAnimation(const std::string &filePath) {
        auto fileFullPath = Application::GetDataPath() + filePath;
        if (!std::filesystem::exists(fileFullPath)) {
            Debug::LogError("File not found: " + fileFullPath);
            return;
        }
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(fileFullPath, aiProcess_Triangulate);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Debug::LogError("Failed to load model: " + fileFullPath);
            return;
        }

        if (scene->mNumAnimations == 0) {
            Debug::LogError("No animations found in the file: " + fileFullPath);
            return;
        }

        const aiAnimation* animation = scene->mAnimations[0];
        AnimationClip clip;
        clip.name = animation->mName.C_Str();
        clip.frameCount = static_cast<unsigned short>(animation->mDuration);
        clip.frameRate = static_cast<unsigned short>(animation->mTicksPerSecond);

        std::vector<aiNodeAnim*> nodeAnims;
        std::unordered_map<std::string, unsigned int> boneNameToIndex;
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            for (unsigned int j = 0; j < mesh->mNumBones; ++j) {
                std::string boneName = mesh->mBones[j]->mName.C_Str();
                clip.boneNames.push_back(boneName);
                boneNameToIndex[boneName] = j;
                //find nodeAnims
                for (unsigned int k = 0; k < animation->mNumChannels; ++k) {
                    auto nodeAnim = animation->mChannels[k];
                    if (nodeAnim->mNodeName.C_Str() == boneName) {
                        nodeAnims.push_back(nodeAnim);
                        break;
                    }
                }
            }
        }
        std::unordered_map<std::string, aiNodeAnim*> boneNameToNodeAnim;
        for (unsigned int k = 0; k < animation->mNumChannels; ++k) {
            aiNodeAnim* nodeAnim = animation->mChannels[k];
            boneNameToNodeAnim[nodeAnim->mNodeName.C_Str()] = nodeAnim;
        }

        unsigned int boneCount = clip.boneNames.size();
        clip.boneFrameMat4s.resize(clip.frameCount, std::vector<glm::mat4>(boneCount));

        const aiMesh* mesh = scene->mMeshes[0];
        auto rootTransform = AiMatrix4x4ToGlm(scene->mRootNode->mTransformation);
        for (unsigned int i = 0; i < clip.frameCount; ++i) {
            std::unordered_map<std::string, glm::mat4> localBoneMatrices;
            for (unsigned int j = 0; j < boneCount; ++j) {
                std::string boneName = clip.boneNames[j];
                auto bone = mesh->mBones[j];
                auto channel = boneNameToNodeAnim[boneName];
                glm::vec3 currentPosition = InterpolatePosition(channel, i);
                glm::quat currentRotation = InterpolateRotation(channel, i);
                glm::vec3 currentScaling = InterpolateScaling(channel, i);

                glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), currentPosition);
                glm::mat4 rotationMatrix = glm::mat4_cast(currentRotation);
                glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), currentScaling);
                glm::mat4 animTransform = translationMatrix * rotationMatrix * scalingMatrix;
                auto parent_transform = glm::mat4(1.0f);;
                const aiNode* boneNode = FindNode(scene->mRootNode, boneName);
                if (boneNode && boneNode->mParent) {
                    std::string parentBoneName = boneNode->mParent->mName.C_Str();
                    auto it = boneNameToIndex.find(parentBoneName);
                    if (it != boneNameToIndex.end()) {
                        unsigned int parent_idx = it->second;
                        parent_transform = clip.boneFrameMat4s[i][parent_idx];
                    }
                }
                clip.boneFrameMat4s[i][j] = parent_transform * animTransform;
                clip.boneFrameMat4s[i][j] = rootTransform * clip.boneFrameMat4s[i][j] * AiMatrix4x4ToGlm(bone->mOffsetMatrix) * glm::inverse(rootTransform);
            }
        }

        std::filesystem::path path(fileFullPath);
        std::string src_file_name = path.filename().stem().string();
        std::string dst_file_name = fmt::format("{}_{}.skeleton_anim", src_file_name, clip.name);
        // 获取最后一层目录
        std::filesystem::path parent_path = path.parent_path();
        std::filesystem::path new_parent_path = parent_path.parent_path() / "animation";
        // 更改文件名
        std::filesystem::path new_path = new_parent_path / dst_file_name;
        clip.Write(new_path.string());
    }


} // DivineBrush