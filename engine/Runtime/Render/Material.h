//
// Created by onelei on 2024/3/14.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <string>
#include <vector>
#include "Shader.h"
#include "../ui/Texture2d.h"
#include "glm/vec3.hpp"

namespace DivineBrush {
    class Material {
    public:
        Material() = default;

        ~Material() = default;

        void Parse(const std::string &materialPath);

        void SetUniformInt(const std::string &shaderPropertyName, int value);

        void SetUniformFloat(const std::string &shaderPropertyName, float value);

        void SetUniformVector3(const std::string &shaderPropertyName, glm::vec3 &value);

        void SetTexture(const std::string &shaderPropertyName, Texture2d *texture);

        void Render(GLuint shaderProgramHandle);

        Shader *GetShader() { return shader; }

        std::vector<std::pair<std::string, Texture2d *>> &GetTextures() { return textures; }

    private:
        Shader *shader = nullptr;
        std::vector<std::pair<std::string, Texture2d *>> textures;
        std::unordered_map<std::string, int> uniformIntMap;
        std::unordered_map<std::string, float> uniformFloatMap;
        std::unordered_map<std::string, glm::vec3> uniformVector3Map;
    };

} // DivineBrush

#endif //ENGINE_MATERIAL_H
