//
// Created by onelei on 2024/3/8.
//

#include <string>
#include <iostream>
//#include <sstream>
#include <fstream>
#include "Shader.h"
#include "../Application.h"
#include "../../depends/debug/debug.h"
#include "../RenderPipeline/RenderPipeline.h"
#include "../../depends/template/ObjectPool.h"
#include "../RenderPipeline/Handler/CompileShaderHandler.h"
#include "../RenderPipeline/Handler/UseShaderProgramHandler.h"
#include "../RenderPipeline/RenderGenerater.h"

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

//        std::ifstream vertex_shader_file(vertex_shader_path);
//        if (!vertex_shader_file.is_open()) {
//            std::cerr << "Error: Failed to open vertex shader file." << std::endl;
//        }
//        std::stringstream buffer;
//        buffer << vertex_shader_file.rdbuf();
//        std::string vertex_shader_text = buffer.str();
//        vertex_shader_file.close();
//
//        std::ifstream fragment_shader_file(fragment_shader_path);
//        if (!fragment_shader_file.is_open()) {
//            std::cerr << "Error: Failed to open fragment shader file." << std::endl;
//        }
//        buffer.clear();
//        buffer.str("");
//        buffer << fragment_shader_file.rdbuf();
//        std::string fragment_shader_text = buffer.str();
//        fragment_shader_file.close();
        std::ifstream vertex_shader_input_file_stream(vertex_shader_path);
        std::string vertex_shader_text((std::istreambuf_iterator<char>(vertex_shader_input_file_stream)),
                                       std::istreambuf_iterator<char>());
        // 读取片段Shader代码
        std::ifstream fragment_shader_input_file_stream(fragment_shader_path);
        std::string fragment_shader_text((std::istreambuf_iterator<char>(fragment_shader_input_file_stream)),
                                         std::istreambuf_iterator<char>());

        CreateProgram(vertex_shader_text.c_str(), fragment_shader_text.c_str());
    }

    void Shader::CreateProgram(const char* vertex_shader_text, const char* fragment_shader_text) {
        shaderProgramHandle = RenderGenerater::CreateShader();
        auto handler = ObjectPool<CompileShaderHandler>::Get();
        handler->vertexShaderSource= static_cast<char *>(malloc(strlen(vertex_shader_text) + 1));
        strcpy(handler->vertexShaderSource, vertex_shader_text);

        handler->fragmentShaderSource= static_cast<char *>(malloc(strlen(fragment_shader_text) + 1));
        strcpy(handler->fragmentShaderSource, fragment_shader_text);

        handler->shaderProgramHandle = shaderProgramHandle;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
    }

    void Shader::Use() const {
        auto handler = ObjectPool<UseShaderProgramHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
    }

} // DivineBrush