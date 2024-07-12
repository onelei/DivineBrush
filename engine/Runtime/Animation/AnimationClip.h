//
// Created by onelei on 2024/5/23.
//

#ifndef ENGINE_ANIMATIONCLIP_H
#define ENGINE_ANIMATIONCLIP_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_set>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <unordered_map>

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

        int AnimationClip::getBoneIndex(const std::string &bone_name) const;

        std::string ReplaceChar(std::string fileName, char oldChar, char newChar) const;

        void Write(std::string filePath) const;

        static void ExportSkeletonAnimation(const std::string &filePath);

        // 线性插值辅助函数
        template<typename T>
        static T Lerp(const T &start, const T &end, float factor) {
            return start + factor * (end - start);
        }

        // 专门为 aiVector3D 定义的 Lerp 函数
        static aiVector3D Lerp(const aiVector3D &start, const aiVector3D &end, float factor) {
            return aiVector3D(
                    start.x + factor * (end.x - start.x),
                    start.y + factor * (end.y - start.y),
                    start.z + factor * (end.z - start.z)
            );
        }

        // 球面线性插值函数
        static glm::quat Slerp(const glm::quat& start, const glm::quat& end, float factor) {
            return glm::slerp(start, end, factor);
        }

// 查找关键帧索引
        static unsigned int FindKeyFrameIndex(const aiNodeAnim* channel, double time, unsigned int numKeys) {
            for (unsigned int i = 0; i < numKeys - 1; ++i) {
                if (time < channel->mPositionKeys[i + 1].mTime) {
                    return i;
                }
            }
            return numKeys - 1;
        }

// 递归计算骨骼的全局变换
        static glm::mat4 CalculateGlobalTransform(const aiNode* node, const glm::mat4& parentTransform) {
            aiVector3D position;
            aiQuaternion rotation;
            aiVector3D scaling;
            node->mTransformation.Decompose(scaling, rotation, position);

            glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z)) *
                                       glm::mat4_cast(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z)) *
                                       glm::scale(glm::mat4(1.0f), glm::vec3(scaling.x, scaling.y, scaling.z));

            glm::mat4 globalTransform = parentTransform * localTransform;

            return globalTransform;
        }

        // 查找当前帧时间所在的键帧索引
        static unsigned int FindPosition(float animationTime, const aiNodeAnim *channel) {
            if (animationTime <= 0) {
                return 0;
            }
            for (unsigned int i = 0; i < channel->mNumPositionKeys - 1; ++i) {
                if (animationTime < channel->mPositionKeys[i + 1].mTime) {
                    return i;
                }
            }
            return channel->mNumPositionKeys - 1;
        }

        static unsigned int FindRotation(float animationTime, const aiNodeAnim *channel) {
            if (animationTime <= 0) {
                return 0;
            }
            for (unsigned int i = 0; i < channel->mNumRotationKeys - 1; ++i) {
                if (animationTime < channel->mRotationKeys[i + 1].mTime) {
                    return i;
                }
            }
            return channel->mNumRotationKeys - 1;
        }

        static unsigned int FindScaling(float animationTime, const aiNodeAnim *channel) {
            if (animationTime <= 0) {
                return 0;
            }
            for (unsigned int i = 0; i < channel->mNumScalingKeys - 1; ++i) {
                if (animationTime < channel->mScalingKeys[i + 1].mTime) {
                    return i;
                }
            }
            return channel->mNumRotationKeys - 1;
        }

        static void Interpolate(aiQuaternion& out, const aiQuaternion& start, const aiQuaternion& end, float factor) {
            aiQuaternion::Interpolate(out, start, end, factor);
            out.Normalize();
        }

        // 递归计算节点的全局变换矩阵
        static glm::mat4 ComputeGlobalTransform(const aiNode* node, const std::unordered_map<std::string, glm::mat4>& boneTransforms) {
            glm::mat4 transform = glm::mat4(1.0f);

            const aiNode* currentNode = node;
            while (currentNode) {
                std::string nodeName(currentNode->mName.C_Str());
                if (boneTransforms.find(nodeName) != boneTransforms.end()) {
                    transform = boneTransforms.at(nodeName) * transform;
                }
                currentNode = currentNode->mParent;
            }

            return transform;
        }

        // 递归更新每个节点的全局变换矩阵
        static void UpdateGlobalTransforms(const aiNode* node, const std::unordered_map<std::string, glm::mat4>& boneTransforms, std::unordered_map<std::string, glm::mat4>& globalTransforms) {
            std::string nodeName(node->mName.C_Str());
            globalTransforms[nodeName] = ComputeGlobalTransform(node, boneTransforms);

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                UpdateGlobalTransforms(node->mChildren[i], boneTransforms, globalTransforms);
            }
        }

        static void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform, const aiAnimation* pAnimation, const std::unordered_map<std::string, unsigned int>& boneMapping, const std::vector<glm::mat4>& BoneOffsets, std::vector<glm::mat4>& BoneTransforms);
        static const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
        static void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
        static void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
        static void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

    private:
        std::string name;
        unsigned short frameCount = 0;
        unsigned short frameRate = 0;
        std::vector<std::string> boneNames;
        std::vector<std::vector<glm::mat4>> boneFrameMat4s;
        std::vector<std::vector<glm::mat3>> boneFrameNormalMat3s;
        float startTime = 0.0f;
        unsigned short currentFrame = 0;
        bool isPlaying = false;

    };

} // DivineBrush

#endif //ENGINE_ANIMATIONCLIP_H
