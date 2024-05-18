//
// Created by onelei on 2024/5/14.
//

#include "Environment.h"
#include "../Render/UniformBufferManager.h"

namespace DivineBrush {
    Environment::Environment() {

    }

    Environment::~Environment() {

    }

    void Environment::SetAmbientColor(glm::vec3 color) {
        ambientColor = color;
        UniformBufferManager::SetUniformInfoVector3("u_ambient", "data.color", ambientColor);
    }

    void Environment::SetAmbientIntensity(float intensity) {
        ambientColorIntensity = intensity;
        UniformBufferManager::SetUniformInfoFloat("u_ambient", "data.intensity", ambientColorIntensity);
    }
} // DivineBrush