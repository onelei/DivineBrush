//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <unordered_map>

namespace DivineBrush {
    class Shader {
    public:
        Shader();

        ~Shader();

        void Parse(const std::string &shaderName);

        void CreateProgram(const std::string &vertex_shader_text, const std::string &fragment_shader_text);

        void Use();

        unsigned int GetProgramId() const { return program_id; }

        static Shader *Find(const std::string &shaderName);

    public:
        std::string shader_name;

    private:
        unsigned int program_id;
        unsigned int shaderProgramHandle = 0;
        static std::unordered_map<std::string, Shader *> shader_map;
    };
} // DivineBrush

#endif //ENGINE_SHADER_H
