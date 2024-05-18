//
// Created by onelei on 2024/5/14.
//

#include <fmt/format.h>
#include "Light.h"
#include "../Render/UniformBufferManager.h"
#include "../Component/Transform.h"
#include "../Component/GameObject.h"
#include <glm/gtx/euler_angles.hpp>
#include "rttr/registration.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Light>("Light")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    std::unordered_map<Light::LightType, unsigned int> Light::lightTypeCounts = {
            {LightType::Sport,       0},
            {LightType::Directional, 0},
            {LightType::Point,       0}
    };

    Light::Light() {
        lightIndex = lightTypeCounts[lightType]++;
        auto lightCount = lightTypeCounts[lightType];
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                UniformBufferManager::SetUniformInfoInt("u_directional_light_array",
                                                        "actually_used_count", lightCount);
                break;
            case Point:
                UniformBufferManager::SetUniformInfoInt("u_point_light_array",
                                                        "actually_used_count", lightCount);
                break;
            case Area:
                break;
        }
    }

    Light::~Light() {

    }

    void Light::SetLightType(Light::LightType type) {
        lightType = type;
    }

    void Light::SetColor(glm::vec3 _color) {
        color = _color;
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                UniformBufferManager::SetUniformInfoVector3("u_directional_light_array",
                                                            fmt::format("data[{}].color", lightIndex), color);
                break;
            case Point:
                UniformBufferManager::SetUniformInfoVector3("u_point_light_array",
                                                            fmt::format("data[{}].color", lightIndex), color);
                break;
            case Area:
                break;
        }
    }

    void Light::SetIntensity(float _intensity) {
        intensity = _intensity;
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                UniformBufferManager::SetUniformInfoFloat("u_directional_light_array",
                                                          fmt::format("data[{}].intensity", lightIndex), intensity);
                break;
            case Point:
                UniformBufferManager::SetUniformInfoFloat("u_point_light_array",
                                                          fmt::format("data[{}].intensity", lightIndex), intensity);
                break;
            case Area:
                break;
        }
    }

    void Light::SetAttenuationConst(float _attenuationConst) {
        attenuationConst = _attenuationConst;
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                break;
            case Point:
                UniformBufferManager::SetUniformInfoFloat("u_point_light_array",
                                                          fmt::format("data[{}].constant", lightIndex),
                                                          attenuationConst);
                break;
            case Area:
                break;
        }
    }

    void Light::SetAttenuationLinear(float _attenuationLinear) {
        attenuationLinear = _attenuationLinear;
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                break;
            case Point:
                UniformBufferManager::SetUniformInfoFloat("u_point_light_array",
                                                          fmt::format("data[{}].linear", lightIndex),
                                                          attenuationLinear);
                break;
            case Area:
                break;
        }
    }

    void Light::SetAttenuationQuadratic(float _attenuationQuadratic) {
        attenuationQuadratic = _attenuationQuadratic;
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional:
                break;
            case Point:
                UniformBufferManager::SetUniformInfoFloat("u_point_light_array",
                                                          fmt::format("data[{}].quadratic", lightIndex),
                                                          attenuationQuadratic);
                break;
            case Area:
                break;
        }
    }

    void Light::OnUpdate() {
        Component::OnUpdate();
        switch (lightType) {
            case LightType::Sport:
                break;
            case Directional: {
                auto rotation = gameObject->GetTransform()->GetRotation();
                auto euler = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x),
                                                glm::radians(rotation.z));
                auto lightRotation = glm::vec3(euler * glm::vec4(0, 0, -1, 0));
                UniformBufferManager::SetUniformInfoVector3("u_directional_light_array",
                                                            fmt::format("data[{}].dir", lightIndex),
                                                            lightRotation);
            }

                break;
            case Point: {
                auto position = gameObject->GetTransform()->GetPosition();
                UniformBufferManager::SetUniformInfoVector3("u_point_light_array",
                                                            fmt::format("data[{}].pos", lightIndex),
                                                            position);
            }
                break;
            case Area:
                break;
        }
    }

} // DivineBrush