//
// Created by onelei on 2024/3/14.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <string>
#include "shader.h"
#include "../ui/texture/texture2d.h"

namespace DivineBrush {
    class Material {
    public:
        Material() = default;

        ~Material() = default;

        void Parse(const std::string &materialPath);

        void SetUniformMatrix4fv(const std::string &shaderPropertyName, float *pointer);

        void SetUniform1i(const std::string &shaderPropertyName, int value);

        void SetTexture(const std::string &shaderPropertyName, Texture2d *texture);

        Shader *GetShader() { return shader; }

        std::vector<std::pair<std::string, Texture2d *>> &GetTextures() { return textures; }

    private:
        Shader *shader = nullptr;
        std::vector<std::pair<std::string, Texture2d *>> textures;
        std::vector<std::pair<std::string, float *>> uniform_matrix4fv_vec;
        std::vector<std::pair<std::string, int>> uniform_1i_vec;
    };

} // DivineBrush

#endif //ENGINE_MATERIAL_H
