//
// Created by onelei on 2024/3/15.
//

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "camera.h"
#include "../object/game_object.h"
#include "rttr/registration.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Camera>("Camera")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Camera::Camera() {
        clear_flag = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        clear_color = glm::vec4(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
    }

    Camera::~Camera() = default;

    void Camera::Clear() {
        glClear(clear_flag);
        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    }

    void Camera::Render() {
        transform = dynamic_cast<Transform *>(GetGameObject()->GetComponent("Transform"));
        view = glm::lookAt(transform->GetPosition(), center, up);
        projection = glm::perspective(glm::radians(fov), aspect, near, far);
    }
} // DivineBrush