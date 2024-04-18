//
// Created by onelei on 2024/3/15.
//

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "../Component/GameObject.h"
#include "rttr/registration.h"
#include "easy/details/profiler_colors.h"
#include "easy/profiler.h"
#include "../RenderPipeline/Handler/SetClearFlagAndClearColorBufferHandler.h"
#include "../../depends/template/ObjectPool.h"
#include "../RenderPipeline/RenderPipeline.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Camera>("Camera")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    std::vector<Camera *> Camera::cameras;
    Camera *Camera::current_camera;

    Camera::Camera() {
        cameras.emplace_back(this);
    }

    Camera::~Camera() {
        auto it = std::find(cameras.begin(), cameras.end(), this);
        if (it != cameras.end()) {
            cameras.erase(it);
        }
    }

    void Camera::Clear() {
        auto handler = ObjectPool<SetClearFlagAndClearColorBufferHandler>::Get();
        handler->clearFlag = clear_flag;
        handler->clearColorR = clear_color.r;
        handler->clearColorG = clear_color.g;
        handler->clearColorB = clear_color.b;
        handler->clearColorA = clear_color.a;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
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
        EASY_FUNCTION(profiler::colors::Magenta); // 标记函数
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