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

    std::vector<Camera *> Camera::cameras;

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
        transform = dynamic_cast<Transform *>(GetGameObject()->GetComponent("Transform"));
        view = glm::lookAt(transform->GetPosition(), center, up);
        projection = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    void Camera::RenderAll(MeshRender *mesh_render) {
        for (auto &camera: cameras) {
            if (camera->GetGameObject()->GetTag() == GameObject::kTagMainCamera) {
                camera->Clear();
            }
            camera->Render();
            //剔除不需要渲染的物体
            //对两个数的位进行逐位的与(AND)操作。如果两个相应的位都为1，则该位的结果为1；否则，为0。
            if((mesh_render->GetGameObject()->GetLayer()&camera->GetCullingMask()) == 0x00){
                continue;
            }
            //从当前Camera获取View Projection
            mesh_render->SetView(camera->GetView());
            mesh_render->SetProjection(camera->GetProjection());
            mesh_render->Render();
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