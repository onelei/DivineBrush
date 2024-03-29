//
// Created by onelei on 2024/3/8.
//

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Shader.h"
#include "../application.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    std::unordered_map<std::string, Shader *> Shader::shader_map;

    Shader::Shader() {

    }

    Shader::~Shader() {

    }

    Shader *Shader::Find(const std::string &shaderName) {
        auto iter = shader_map.find(shaderName);
        if (iter != shader_map.end()) {
            return iter->second;
        }
        auto shader = new Shader();
        shader->Parse(shaderName);
        shader_map.insert(std::pair<std::string, Shader *>(shaderName, shader));
        return shader;
    }

    void Shader::Parse(const std::string &shaderName) {
        this->shader_name = shaderName;
        auto vertex_shader_path = Application::GetDataPath() + shaderName + ".vs";
        auto fragment_shader_path = Application::GetDataPath() + shaderName + ".fs";

        std::ifstream vertex_shader_file(vertex_shader_path);
        if (!vertex_shader_file.is_open()) {
            std::cerr << "Error: Failed to open vertex shader file." << std::endl;
        }
        std::stringstream buffer;
        buffer << vertex_shader_file.rdbuf();
        std::string vertex_shader_text = buffer.str();
        vertex_shader_file.close();

        std::ifstream fragment_shader_file(fragment_shader_path);
        if (!fragment_shader_file.is_open()) {
            std::cerr << "Error: Failed to open fragment shader file." << std::endl;
        }
        buffer.clear();
        buffer.str("");
        buffer << fragment_shader_file.rdbuf();
        std::string fragment_shader_text = buffer.str();
        fragment_shader_file.close();

        CreateProgram(vertex_shader_text.c_str(), fragment_shader_text.c_str());
    }

    void Shader::CreateProgram(const char *vertex_shader_text, const char *fragment_shader_text) {
        //创建顶点Shader
        auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        //指定Shader源码
        glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
        //编译Shader
        glCompileShader(vertex_shader);
        //获取编译结果
        GLint compile_status = GL_FALSE;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar message[256];
            glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
            DEBUG_LOG_ERROR("compile vertex shader error:{}", message);
        }

        //创建片段Shader
        auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        //指定Shader源码
        glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
        //编译Shader
        glCompileShader(fragment_shader);
        //获取编译结果
        compile_status = GL_FALSE;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar message[256];
            glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
            DEBUG_LOG_ERROR("compile fragment shader error:{}", message);
        }

        //创建GPU程序
        program_id = glCreateProgram();
        //附加Shader
        glAttachShader(program_id, vertex_shader);
        glAttachShader(program_id, fragment_shader);
        //Link
        glLinkProgram(program_id);
        //获取编译结果
        GLint link_status = GL_FALSE;
        glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
        if (link_status == GL_FALSE) {
            GLchar message[256];
            glGetProgramInfoLog(program_id, sizeof(message), 0, message);
            DEBUG_LOG_ERROR("link shader error:{}", message);
        }
    }

} // DivineBrush