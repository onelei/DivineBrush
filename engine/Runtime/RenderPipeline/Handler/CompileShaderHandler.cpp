//
// Created by onelei on 2024/4/10.
//

#include "CompileShaderHandler.h"
#include "../../../depends/debug/debug.h"
#include <GL/glew.h>
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    CompileShaderHandler::CompileShaderHandler() {
        renderCommand = DivineBrush::RenderCommand::CompileShader;
    }

    CompileShaderHandler::~CompileShaderHandler() {

    }

    void CompileShaderHandler::Run() {
        RenderCommandHandler::Run();
        //创建顶点Shader
        auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//        auto gl_error_code = glGetError();
//        if (gl_error_code != GL_NO_ERROR) {
//            DEBUG_LOG_ERROR("gl_error_code: {}", gl_error_code);
//        }
        //指定Shader源码
        glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
        //编译Shader
        glCompileShader(vertex_shader);
        //获取编译结果
        GLint compile_status = GL_FALSE;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar message[256];
            glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
            DEBUG_LOG_ERROR("compile vertex shader error:{}", message);
            return;
        }

        //创建片段Shader
        auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        //指定Shader源码
        glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
        //编译Shader
        glCompileShader(fragment_shader);
        //获取编译结果
        compile_status = GL_FALSE;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar message[256];
            glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
            DEBUG_LOG_ERROR("compile fragment shader error:{}", message);
            return;
        }
        //创建GPU程序
        auto program_id = glCreateProgram();
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
            return;
        }

        RenderGenerater::SetShader(shaderProgramHandle, program_id);
    }

    void CompileShaderHandler::Clear() {
        RenderCommandHandler::Clear();
        free(vertexShaderSource);
        free(fragmentShaderSource);
        DivineBrush::ObjectPool<DivineBrush::CompileShaderHandler>::Release(this);
    }
} // DivineBrush