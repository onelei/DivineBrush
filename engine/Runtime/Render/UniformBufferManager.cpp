//
// Created by onelei on 2024/5/17.
//

#include <fmt/format.h>
#include <GL/glew.h>
#include "UniformBufferManager.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
//最大方向光数量
#define MAX_DIRECT_LIGHT_NUM 8
//最大点光源数量
#define MAX_POINT_LIGHT_NUM 8

namespace DivineBrush {
    std::unordered_map<std::string, UniformBuffer> UniformBufferManager::uniformBuffers;
    std::unordered_map<std::string, std::vector<UniformInfo>> UniformBufferManager::uniformInfos;

    void UniformBufferManager::Init() {
        uniformBuffers["u_ambient"] = {
                "u_ambient", "AmbientBlock", 16, 0, 0
        };
        uniformBuffers["u_directional_light_array"] = {
                "u_directional_light_array", "DirectionalLightBlock",
                32 * MAX_DIRECT_LIGHT_NUM + sizeof(int), 1, 0
        };
        uniformBuffers["u_point_light_array"] = {
                "u_point_light_array", "PointLightBlock",
                48 * MAX_POINT_LIGHT_NUM + sizeof(int), 2, 0
        };
        //环境光
        uniformInfos["AmbientBlock"] = {
                {"data.color",     0,  sizeof(glm::vec3)},
                {"data.intensity", 12, sizeof(float)}
        };
        //平行光
        auto directLightUniformInfos = uniformInfos["DirectionalLightBlock"] = {};
        for (int i = 0; i < MAX_DIRECT_LIGHT_NUM; ++i) {
            directLightUniformInfos.push_back({fmt::format("data[{}].dir", i), 32 * i + 0, sizeof(glm::vec3)});
            directLightUniformInfos.push_back({fmt::format("data[{}].color", i), 32 * i + 16, sizeof(glm::vec3)});
            directLightUniformInfos.push_back({fmt::format("data[{}].intensity", i), 32 * i + 28, sizeof(float)});
        }
        directLightUniformInfos.push_back({"actually_used_count", 32 * MAX_DIRECT_LIGHT_NUM, sizeof(int)});

        //点光源
        auto pointLightUniformInfos = uniformInfos["PointLightBlock"] = {};
        for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i) {
            pointLightUniformInfos.push_back({fmt::format("data[{}].pos", i), 48 * i + 0, sizeof(glm::vec3)});
            pointLightUniformInfos.push_back({fmt::format("data[{}].color", i), 48 * i + 16, sizeof(glm::vec3)});
            pointLightUniformInfos.push_back({fmt::format("data[{}].intensity", i), 48 * i + 28, sizeof(float)});
            pointLightUniformInfos.push_back({fmt::format("data[{}].constant", i), 48 * i + 32, sizeof(float)});
            pointLightUniformInfos.push_back({fmt::format("data[{}].linear", i), 48 * i + 36, sizeof(float)});
            pointLightUniformInfos.push_back({fmt::format("data[{}].quadratic", i), 48 * i + 40, sizeof(float)});
        }
        pointLightUniformInfos.push_back({"actually_used_count", 48 * MAX_POINT_LIGHT_NUM, sizeof(int)});

        CreateUniformBuffer();
    }

    void UniformBufferManager::CreateUniformBuffer() {
        for (auto &v: uniformBuffers) {
            auto uniformBuffer = v.second;
            glGenBuffers(1, &uniformBuffer.buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer.buffer);
            glBufferData(GL_UNIFORM_BUFFER, uniformBuffer.size, nullptr, GL_STATIC_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER, uniformBuffer.bind, uniformBuffer.buffer);
        }
    }

    void
    UniformBufferManager::SetUniformInfoFloat(const std::string &name, const std::string &memberName, float value) {
        auto data = malloc(sizeof(float));
        memcpy(data, &value, sizeof(float));
        RenderCommandBuffer::UpdateUBODataHandler(name, memberName, data);
    }

    void UniformBufferManager::SetUniformInfoVector3(const std::string &name, const std::string &memberName,
                                                     glm::vec3 &value) {
        auto data = malloc(sizeof(glm::vec3));
        memcpy(data, &value, sizeof(glm::vec3));
        RenderCommandBuffer::UpdateUBODataHandler(name, memberName, data);
    }

    void UniformBufferManager::SetUniformInfoInt(const std::string &name, const std::string &memberName, int value) {
        auto data = malloc(sizeof(int));
        memcpy(data, &value, sizeof(int));
        RenderCommandBuffer::UpdateUBODataHandler(name, memberName, data);
    }

    bool UniformBufferManager::TryGetUniformBuffer(const std::string &name, UniformBuffer *&result) {
        auto it = uniformBuffers.find(name);
        if (it != uniformBuffers.end()) {
            result = &it->second;
            return true;
        } else {
            result = nullptr;
            return false;
        }
    }

    bool UniformBufferManager::TryGetUniformInfos(const std::string &name, std::vector<UniformInfo> *&results) {
        auto it = uniformInfos.find(name);
        if (it != uniformInfos.end()) {
            results = &it->second;
            return true;
        } else {
            results = nullptr;
            return false;
        }
    }

    void UniformBufferManager::Bind(GLuint shaderProgramId) {
        for (auto &v:uniformBuffers){
           auto blockIndex = glGetUniformBlockIndex(shaderProgramId, v.second.name.c_str());
           if (blockIndex != GL_INVALID_INDEX) {
               glUniformBlockBinding(shaderProgramId, blockIndex, v.second.bind);
           }
        }
    }

} // DivineBrush