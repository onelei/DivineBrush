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

        // Assuming the first animation
        const aiAnimation* animation = scene->mAnimations[0];
        AnimationClip clip;
        clip.name = animation->mName.C_Str();
        clip.frameCount = static_cast<unsigned short>(animation->mDuration);
        clip.frameRate = static_cast<unsigned short>(animation->mTicksPerSecond);

        // 获取所有骨骼的名称集合
        std::unordered_set<std::string> boneNamesSet;
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            for (unsigned int j = 0; j < mesh->mNumBones; ++j) {
                boneNamesSet.insert(mesh->mBones[j]->mName.C_Str());
            }
        }

        // 过滤动画通道，只保留对应于骨骼的通道
        std::vector<aiNodeAnim*> validChannels;
        for (unsigned int i = 0; i < animation->mNumChannels; ++i) {
            aiNodeAnim* channel = animation->mChannels[i];
            auto boneName = channel->mNodeName.C_Str();
            if (boneNamesSet.find(boneName) != boneNamesSet.end()) {
                clip.boneNames.push_back(boneName);
                validChannels.push_back(channel);
            }
        }

        unsigned int boneCount = validChannels.size();
        clip.boneFrameMat4s.resize(clip.frameCount, std::vector<glm::mat4>(boneCount));

        // 遍历每一帧
        for (unsigned int i = 0; i < clip.frameCount; ++i) {
            for (unsigned int j = 0; j < boneCount; ++j) {
                aiNodeAnim* channel = validChannels[j];

                // Interpolate position
                aiVector3D position;
                if (channel->mNumPositionKeys > 1) {
                    aiVectorKey* keys = channel->mPositionKeys;
                    unsigned int keyIndex = static_cast<unsigned int>(i * (channel->mNumPositionKeys - 1) / clip.frameCount);
                    position = keys[keyIndex].mValue;
                } else {
                    position = channel->mPositionKeys[0].mValue;
                }

                // Interpolate rotation
                aiQuaternion rotation;
                if (channel->mNumRotationKeys > 1) {
                    aiQuatKey* keys = channel->mRotationKeys;
                    unsigned int keyIndex = static_cast<unsigned int>(i * (channel->mNumRotationKeys - 1) / clip.frameCount);
                    rotation = keys[keyIndex].mValue;
                } else {
                    rotation = channel->mRotationKeys[0].mValue;
                }

                // Interpolate scaling
                aiVector3D scaling;
                if (channel->mNumScalingKeys > 1) {
                    aiVectorKey* keys = channel->mScalingKeys;
                    unsigned int keyIndex = static_cast<unsigned int>(i * (channel->mNumScalingKeys - 1) / clip.frameCount);
                    scaling = keys[keyIndex].mValue;
                } else {
                    scaling = channel->mScalingKeys[0].mValue;
                }

                // Create transformation matrices
                glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
                glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
                glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaling.x, scaling.y, scaling.z));

                // Combine transformations
                glm::mat4 mat = translationMatrix * rotationMatrix * scalingMatrix;

                // Store the transformation matrix
                clip.boneFrameMat4s[i][j] = glm::transpose(mat);
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


    void AnimationClip::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform, const aiAnimation* pAnimation, const std::unordered_map<std::string, unsigned int>& boneMapping, const std::vector<glm::mat4>& BoneOffsets, std::vector<glm::mat4>& BoneTransforms) {
        std::string NodeName(pNode->mName.data);

        const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

        glm::mat4 NodeTransformation = glm::mat4(1.0f);

        if (pNodeAnim) {
            aiVector3D Scaling;
            CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
            glm::mat4 ScalingM = glm::scale(glm::mat4(1.0f), glm::vec3(Scaling.x, Scaling.y, Scaling.z));

            aiQuaternion RotationQ;
            CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
            glm::mat4 RotationM = glm::mat4_cast(glm::quat(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z));

            aiVector3D Translation;
            CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
            glm::mat4 TranslationM = glm::translate(glm::mat4(1.0f), glm::vec3(Translation.x, Translation.y, Translation.z));

            NodeTransformation = TranslationM * RotationM * ScalingM;
        }

        glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

        if (boneMapping.find(NodeName) != boneMapping.end()) {
            unsigned int BoneIndex = boneMapping.at(NodeName);
            BoneTransforms[BoneIndex] = GlobalTransformation * BoneOffsets[BoneIndex];
        }

        for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
            ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation, pAnimation, boneMapping, BoneOffsets, BoneTransforms);
        }
    }

    const aiNodeAnim* AnimationClip::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName) {
        for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
            if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }
        return nullptr;
    }

    void AnimationClip::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim) {
        if (pNodeAnim->mNumPositionKeys == 1) {
            Out = pNodeAnim->mPositionKeys[0].mValue;
            return;
        }

        unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
        unsigned int NextPositionIndex = (PositionIndex + 1);
        assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
        float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
        const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
        Out = Start + Factor * (End - Start);
    }

    void AnimationClip::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim) {
        if (pNodeAnim->mNumRotationKeys == 1) {
            Out = pNodeAnim->mRotationKeys[0].mValue;
            return;
        }

        unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
        unsigned int NextRotationIndex = (RotationIndex + 1);
        assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
        float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
        const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
        aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
        Out = Out.Normalize();
    }

    void AnimationClip::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim) {
        if (pNodeAnim->mNumScalingKeys == 1) {
            Out = pNodeAnim->mScalingKeys[0].mValue;
            return;
        }

        unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
        unsigned int NextScalingIndex = (ScalingIndex + 1);
        assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
        float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
        const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
        Out = Start + Factor * (End - Start);
    }

    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim) {
        for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
                return i;
            }
        }
        assert(0);
        return 0;
    }

    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim) {
        for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
                return i;
            }
        }
        assert(0);
        return 0;
    }

    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim) {
        for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
                return i;
            }
        }
        assert(0);
        return 0;
    }
} // DivineBrush