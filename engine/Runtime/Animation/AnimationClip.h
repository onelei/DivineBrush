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
        static glm::quat Slerp(const glm::quat &start, const glm::quat &end, float factor) {
            return glm::slerp(start, end, factor);
        }

        // 查找关键帧索引
        static unsigned int FindKeyFrameIndex(const aiNodeAnim *channel, double time, unsigned int numKeys) {
            for (unsigned int i = 0; i < numKeys - 1; ++i) {
                if (time < channel->mPositionKeys[i + 1].mTime) {
                    return i;
                }
            }
            return numKeys - 1;
        }

        // 递归计算骨骼的全局变换
        static glm::mat4 CalculateGlobalTransform(const aiNode *node, const glm::mat4 &parentTransform) {
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

        static void Interpolate(aiQuaternion &out, const aiQuaternion &start, const aiQuaternion &end, float factor) {
            aiQuaternion::Interpolate(out, start, end, factor);
            out.Normalize();
        }

        // 递归计算节点的全局变换矩阵
        static glm::mat4
        ComputeGlobalTransform(const aiNode *node, const std::unordered_map<std::string, glm::mat4> &boneTransforms) {
            glm::mat4 transform = glm::mat4(1.0f);

            const aiNode *currentNode = node;
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
        static void
        UpdateGlobalTransforms(const aiNode *node, const std::unordered_map<std::string, glm::mat4> &boneTransforms,
                               std::unordered_map<std::string, glm::mat4> &globalTransforms) {
            std::string nodeName(node->mName.C_Str());
            globalTransforms[nodeName] = ComputeGlobalTransform(node, boneTransforms);

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                UpdateGlobalTransforms(node->mChildren[i], boneTransforms, globalTransforms);
            }
        }

        static // 插值函数
        glm::vec3 InterpolatePosition(aiNodeAnim* channel, unsigned int frame) {
            if (channel->mNumPositionKeys == 1) return glm::vec3(channel->mPositionKeys[0].mValue.x, channel->mPositionKeys[0].mValue.y, channel->mPositionKeys[0].mValue.z);

            for (unsigned int i = 0; i < channel->mNumPositionKeys - 1; i++) {
                if (frame < channel->mPositionKeys[i + 1].mTime) {
                    float t = (frame - channel->mPositionKeys[i].mTime) / (channel->mPositionKeys[i + 1].mTime - channel->mPositionKeys[i].mTime);
                    glm::vec3 start(channel->mPositionKeys[i].mValue.x, channel->mPositionKeys[i].mValue.y, channel->mPositionKeys[i].mValue.z);
                    glm::vec3 end(channel->mPositionKeys[i + 1].mValue.x, channel->mPositionKeys[i + 1].mValue.y, channel->mPositionKeys[i + 1].mValue.z);
                    return glm::mix(start, end, t);
                }
            }
            return glm::vec3(0.0f);
        }

        static glm::quat InterpolateRotation(aiNodeAnim* channel, unsigned int frame) {
            if (channel->mNumRotationKeys == 1) return glm::quat(channel->mRotationKeys[0].mValue.w, channel->mRotationKeys[0].mValue.x, channel->mRotationKeys[0].mValue.y, channel->mRotationKeys[0].mValue.z);

            for (unsigned int i = 0; i < channel->mNumRotationKeys - 1; i++) {
                if (frame < channel->mRotationKeys[i + 1].mTime) {
                    float t = (frame - channel->mRotationKeys[i].mTime) / (channel->mRotationKeys[i + 1].mTime - channel->mRotationKeys[i].mTime);
                    glm::quat start(channel->mRotationKeys[i].mValue.w, channel->mRotationKeys[i].mValue.x, channel->mRotationKeys[i].mValue.y, channel->mRotationKeys[i].mValue.z);
                    glm::quat end(channel->mRotationKeys[i + 1].mValue.w, channel->mRotationKeys[i + 1].mValue.x, channel->mRotationKeys[i + 1].mValue.y, channel->mRotationKeys[i + 1].mValue.z);
                    return glm::slerp(start, end, t);
                }
            }
            return glm::quat();
        }

        static glm::vec3 InterpolateScaling(aiNodeAnim* channel, unsigned int frame) {
            if (channel->mNumScalingKeys == 1) return glm::vec3(channel->mScalingKeys[0].mValue.x, channel->mScalingKeys[0].mValue.y, channel->mScalingKeys[0].mValue.z);

            for (unsigned int i = 0; i < channel->mNumScalingKeys - 1; i++) {
                if (frame < channel->mScalingKeys[i + 1].mTime) {
                    float t = (frame - channel->mScalingKeys[i].mTime) / (channel->mScalingKeys[i + 1].mTime - channel->mScalingKeys[i].mTime);
                    glm::vec3 start(channel->mScalingKeys[i].mValue.x, channel->mScalingKeys[i].mValue.y, channel->mScalingKeys[i].mValue.z);
                    glm::vec3 end(channel->mScalingKeys[i + 1].mValue.x, channel->mScalingKeys[i + 1].mValue.y, channel->mScalingKeys[i + 1].mValue.z);
                    return glm::mix(start, end, t);
                }
            }
            return glm::vec3(1.0f);
        }
        static void CalculateGlobalTransform(aiNode* node, const std::unordered_map<std::string, glm::mat4>& boneOffsetMatrices,
                                             const std::unordered_map<std::string, glm::mat4>& boneTransforms,
                                             std::unordered_map<std::string, glm::mat4>& globalTransforms,
                                             const glm::mat4& parentTransform = glm::mat4(1.0f)) {
            std::string nodeName(node->mName.C_Str());
            glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

            if (boneTransforms.find(nodeName) != boneTransforms.end()) {
                nodeTransform = boneTransforms.at(nodeName);
            }

            glm::mat4 globalTransform = parentTransform * nodeTransform;
            globalTransforms[nodeName] = globalTransform;

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                CalculateGlobalTransform(node->mChildren[i], boneOffsetMatrices, boneTransforms, globalTransforms, globalTransform);
            }
        }


        // Function to convert aiMatrix4x4 to glm::mat4
        static glm::mat4 AiMatrix4x4ToGlm(const aiMatrix4x4& from) {
            glm::mat4 to;
            to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
            to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
            to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
            to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
            return to;
        }

        static void ProcessNodeHierarchy(const aiNode* node, const aiAnimation* animation, float currentTime, const glm::mat4& parentTransform, std::unordered_map<std::string, glm::mat4>& boneTransforms) {

        }

        static const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string& nodeName)
        {
            // 遍历动画的所有通道
            for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
                const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

                // 检查通道名称是否与目标名称匹配
                if (std::string(pNodeAnim->mNodeName.data) == nodeName) {
                    return pNodeAnim;
                }
            }

            // 找不到匹配的通道，返回空指针
            return nullptr;
        }

        static void CalculateBoneTransform(aiNode* node, const glm::mat4& parentTransform, std::unordered_map<std::string, glm::mat4>& boneTransforms, const std::unordered_map<std::string, glm::mat4>& boneOffsetMatrices, const std::unordered_map<std::string, glm::mat4>& boneLocalTransforms) {
            std::string nodeName(node->mName.C_Str());
            glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

            if (boneLocalTransforms.find(nodeName) != boneLocalTransforms.end()) {
                nodeTransform = boneLocalTransforms.at(nodeName);
            }

            glm::mat4 globalTransform = parentTransform * nodeTransform;

            if (boneOffsetMatrices.find(nodeName) != boneOffsetMatrices.end()) {
                boneTransforms[nodeName] = globalTransform * boneOffsetMatrices.at(nodeName);
            }

            for (unsigned int i = 0; i < node->mNumChildren; i++) {
                CalculateBoneTransform(node->mChildren[i], globalTransform, boneTransforms, boneOffsetMatrices, boneLocalTransforms);
            }
        }

        static void CalculateBoneTransforms(const aiNode* node, const glm::mat4& parentTransform,
                                                    const std::unordered_map<std::string, glm::mat4>& boneTransforms,
                                                    std::vector<glm::mat4>& finalTransforms,
                                                    const std::unordered_map<std::string, glm::mat4>& boneOffsetMatrices) {
            std::string nodeName = node->mName.C_Str();
            glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

            if (boneTransforms.find(nodeName) != boneTransforms.end()) {
                nodeTransform = boneTransforms.at(nodeName);
            }

            glm::mat4 globalTransform = parentTransform * nodeTransform;

            if (boneOffsetMatrices.find(nodeName) != boneOffsetMatrices.end()) {
                unsigned int boneIndex = std::distance(boneOffsetMatrices.begin(), boneOffsetMatrices.find(nodeName));
                finalTransforms[boneIndex] = globalTransform * boneOffsetMatrices.at(nodeName);
            }

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                CalculateBoneTransforms(node->mChildren[i], globalTransform, boneTransforms, finalTransforms, boneOffsetMatrices);
            }
        }

        static const aiNode* FindNode(const aiNode* rootNode, const std::string& nodeName) {
            if (rootNode->mName.C_Str() == nodeName) {
                return rootNode;
            }

            for (unsigned int i = 0; i < rootNode->mNumChildren; ++i) {
                const aiNode* foundNode = FindNode(rootNode->mChildren[i], nodeName);
                if (foundNode) {
                    return foundNode;
                }
            }

            return nullptr;
        }

        static void CalculateInitialGlobalTransforms(const aiNode* node, const glm::mat4& parentTransform, std::unordered_map<std::string, glm::mat4>& boneInitialGlobalTransforms) {
            std::string nodeName = node->mName.C_Str();
            glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

            glm::mat4 globalTransform = parentTransform * nodeTransform;
            boneInitialGlobalTransforms[nodeName] = globalTransform;

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                CalculateInitialGlobalTransforms(node->mChildren[i], globalTransform, boneInitialGlobalTransforms);
            }
        }

        static glm::mat4 EvaluateGlobalTransform(const aiNode* rootNode, const std::string& boneName, const std::unordered_map<std::string, glm::mat4>& boneTransforms) {
            const aiNode* node = FindNode(rootNode,boneName);
            if (!node) {
                return glm::mat4(1.0f);
            }

            glm::mat4 globalTransform = glm::mat4(1.0f);
            while (node) {
                std::string nodeName = node->mName.C_Str();
                glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

                if (boneTransforms.find(nodeName) != boneTransforms.end()) {
                    nodeTransform = boneTransforms.at(nodeName);
                }

                globalTransform = nodeTransform * globalTransform;

                node = node->mParent;
            }

            return globalTransform;
        }

        // 递归地计算全局变换矩阵
        static void CalculateGlobalTransform(const aiNode* node, const std::unordered_map<std::string, glm::mat4>& boneOffsetMatrices, const std::unordered_map<std::string, glm::mat4>& boneTransforms, glm::mat4 parentTransform, std::unordered_map<std::string, glm::mat4>& globalTransforms) {
            std::string nodeName(node->mName.C_Str());
            glm::mat4 nodeTransform = AiMatrix4x4ToGlm(node->mTransformation);

            auto it = boneTransforms.find(nodeName);
            if (it != boneTransforms.end()) {
                nodeTransform = it->second;
            }

            glm::mat4 globalTransform = parentTransform * nodeTransform;
            globalTransforms[nodeName] = globalTransform;

            for (unsigned int i = 0; i < node->mNumChildren; ++i) {
                CalculateGlobalTransform(node->mChildren[i], boneOffsetMatrices, boneTransforms, globalTransform, globalTransforms);
            }
        }

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
