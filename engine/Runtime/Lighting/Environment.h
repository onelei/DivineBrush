//
// Created by onelei on 2024/5/14.
//

#ifndef ENGINE_ENVIRONMENT_H
#define ENGINE_ENVIRONMENT_H

#include <glm/vec3.hpp>

namespace DivineBrush {

    class Environment {
    public:

        Environment();

        ~Environment();

        void SetAmbientColor(glm::vec3 color);

        void SetAmbientIntensity(float intensity);

        glm::vec3 &GetAmbientColor() {
            return ambientColor;
        }

        float GetAmbientIntensity() const {
            return ambientColorIntensity;
        }

    private:
        glm::vec3 ambientColor = glm::vec3(1.0f);
        float ambientColorIntensity = 1.0f;
    };

} // DivineBrush

#endif //ENGINE_ENVIRONMENT_H
