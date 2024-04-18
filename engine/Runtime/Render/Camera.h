//
// Created by onelei on 2024/3/15.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <functional>
#include <utility>
#include "../Component/Component.h"
#include "../Component/transform.h"
#include "MeshRender.h"

namespace DivineBrush {
    class Camera : public Component {

    public:
        Camera();

        ~Camera();

    public:

        enum class CameraMode : unsigned char {
            Perspective,
            Orthographic,
        };

        void SetFov(float fov) {
            this->fov = fov;
        }

        void SetAspect(float aspect) {
            this->aspect = aspect;
        }

        void SetNear(float near) {
            this->near = near;
        }

        void SetFar(float far) {
            this->far = far;
        }

        void SetDepth(int depth);

        float GetFov() {
            return this->fov;
        }

        float GetAspect() {
            return this->aspect;
        }

        float GetNear() {
            return this->near;
        }

        float GetFar() {
            return this->far;
        }

        int GetDepth() {
            return this->depth;
        }

        void SetCullingMask(unsigned char culling_mask) {
            this->culling_mask = culling_mask;
        }

        unsigned char GetCullingMask() {
            return this->culling_mask;
        }

        void SetCenter(glm::vec3 center) {
            this->center = center;
        }

        void SetUp(glm::vec3 up) {
            this->up = up;
        }

        void SetMode(CameraMode mode) {
            this->mode = mode;
        }

        CameraMode GetMode() {
            return this->mode;
        }

        glm::vec3 GetCenter() {
            return this->center;
        }

        glm::vec3 GetUp() {
            return this->up;
        }

        void SetClearColor(glm::vec4 clear_color) {
            this->clear_color = clear_color;
        }

        glm::vec4 GetClearColor() {
            return this->clear_color;
        }

        void SetClearFlag(unsigned int clear_flag) {
            this->clear_flag = clear_flag;
        }

        unsigned int GetClearFlag() {
            return this->clear_flag;
        }

        glm::mat4 &GetView() {
            return view;
        }

        glm::mat4 &GetProjection() {
            return projection;
        }

        void SetLeft(float left) {
            this->left = left;
        }

        void SetRight(float right) {
            this->right = right;
        }

        void SetBottom(float bottom) {
            this->bottom = bottom;
        }

        void SetTop(float top) {
            this->top = top;
        }

        void SetOrthographic(float left, float right, float bottom, float top) {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
        }

        void Clear();

        void Render();

        static void RenderAll();

        static Camera *GetCurrentCamera() {
            return current_camera;
        }

    private:
        float fov = 45.0f;
        float aspect = 1.0f;
        float near = 0.1f;
        float far = 100.0f;
        int depth = 0;
        unsigned char culling_mask = 0x01;
        glm::vec3 center;
        glm::vec3 up;

        CameraMode mode = CameraMode::Perspective;
        float left;
        float right;
        float bottom;
        float top;

        Transform *transform;
        unsigned int clear_flag = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
        glm::vec4 clear_color = glm::vec4(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        glm::mat4 view;
        glm::mat4 projection;
        static std::vector<Camera *> cameras;
        static Camera *current_camera;

        static void SortByDepth();
    };

} // DivineBrush

#endif //ENGINE_CAMERA_H
