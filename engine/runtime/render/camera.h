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
#include "../object/component.h"
#include "../object/transform.h"
#include "mesh_render.h"

namespace DivineBrush {
    class Camera : public Component {

    public:
        Camera();

        ~Camera();

    public:
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

        void SetCenter(glm::vec3 center) {
            this->center = center;
        }

        void SetUp(glm::vec3 up) {
            this->up = up;
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

        glm::mat4 GetView() {
            return view;
        }

        glm::mat4 GetProjection() {
            return projection;
        }

        void Clear();
        void Render();
        static void RenderAll(MeshRender *mesh_render);

    private:
        float fov = 45.0f;
        float aspect = 1.0f;
        float near = 0.1f;
        float far = 100.0f;
        glm::vec3 center;
        glm::vec3 up;

        Transform *transform;
        GLbitfield clear_flag = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        glm::vec4 clear_color;

        glm::mat4 view;
        glm::mat4 projection;
        static std::vector<Camera *> cameras;
        static Camera *camera;
        static Camera *main_camera;
    };

} // DivineBrush

#endif //ENGINE_CAMERA_H
