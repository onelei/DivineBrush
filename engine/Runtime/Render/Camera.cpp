//
// Created by onelei on 2024/3/15.
//

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Camera.h"
#include "../Component/GameObject.h"
#include "rttr/registration.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Camera>("Camera")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    std::vector<Camera *> Camera::cameras;
    Camera *Camera::current_camera;

    Camera::Camera() {
        clear_flag = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        clear_color = glm::vec4(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
        cameras.emplace_back(this);
    }

    Camera::~Camera() {
        auto it = std::find(cameras.begin(), cameras.end(), this);
        if (it != cameras.end()) {
            cameras.erase(it);
        }
    }

    void Camera::Clear() {
        glClear(clear_flag);
        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    }

    void Camera::Render() {
        transform = dynamic_cast<Transform *>(gameObject->GetComponent("Transform"));
        view = glm::lookAt(transform->GetPosition(), center, up);
        switch (mode) {
            case CameraMode::Perspective:
                projection = glm::perspective(glm::radians(fov), aspect, near, far);
                break;
            case CameraMode::Orthographic:
                projection = glm::ortho(left, right, bottom, top, near, far);
                break;
        }
    }

    void Camera::RenderAll() {
        for (auto &camera: cameras) {
            if (camera->GetGameObject()->GetTag() == GameObject::kTagMainCamera) {
                camera->Clear();
            }
            camera->Render();
            current_camera = camera;
            GameObject::RenderAll();
        }
    }

    void Camera::SetDepth(int depth) {
        if (this->depth == depth) {
            return;
        }
        this->depth = depth;
        SortByDepth();
    }

    void Camera::SortByDepth() {
        std::sort(cameras.begin(), cameras.end(), [](Camera *a, Camera *b) {
            return a->GetDepth() < b->GetDepth();
        });
    }

} // DivineBrush