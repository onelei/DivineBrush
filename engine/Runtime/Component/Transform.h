//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>

namespace DivineBrush {
    class Transform : public Component {
    public:
        Transform();

        ~Transform();

    public:
        void SetPosition(glm::vec3 vec3) {
            this->position = vec3;
        }

        void SetRotation(glm::vec3 vec3) {
            this->rotation = vec3;
        }

        void SetScale(glm::vec3 vec3) {
            this->scale = vec3;
        }

        glm::vec3 GetPosition() {
            return this->position;
        }

        glm::vec3 GetRotation() {
            return this->rotation;
        }

        glm::vec3 GetScale() {
            return this->scale;
        }

    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
}
#endif //ENGINE_TRANSFORM_H
