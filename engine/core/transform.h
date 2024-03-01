//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include "component.h"
#include <glm/glm.hpp>

namespace DivineBrush {
    class Transform : public Component {
    public:
        Transform() = default;

        ~Transform() override = default;

    public:
        void setPosition(glm::vec3 position) {
            this->_position = position;
        }

        void setRotation(glm::vec3 rotation) {
            this->_rotation = rotation;
        }

        void setScale(glm::vec3 scale) {
            this->_scale = scale;
        }

        glm::vec3 getPosition() {
            return this->_position;
        }

        glm::vec3 getRotation() {
            return this->_rotation;
        }

        glm::vec3 getScale() {
            return this->_scale;
        }

    private:
        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    };
}
#endif //ENGINE_TRANSFORM_H
