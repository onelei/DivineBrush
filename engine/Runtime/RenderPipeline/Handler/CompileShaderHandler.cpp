//
// Created by onelei on 2024/4/10.
//

#include "CompileShaderHandler.h"
#include "../../../depends/debug/debug.h"
#include <GL/glew.h>
#include "../RenderPipeline.h"

namespace DivineBrush {
    void CompileShaderHandler::Run() {
        RenderCommandHandler::Run();
        //创建顶点Shader
        auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        //指定Shader源码
        const GLchar *vertCode = vertexShaderSource.c_str();
        glShaderSource(vertex_shader, 1, &vertCode, nullptr);
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
        const GLchar *fragCode = fragmentShaderSource.c_str();
        glShaderSource(fragment_shader, 1, &fragCode, nullptr);
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
        }

        RenderPipeline::GetInstance().GetRenderProgramGenerater()->SetShader(shaderProgramHandle, program_id);
    }

    void CompileShaderHandler::Clear() {
        RenderCommandHandler::Clear();
    }
} // DivineBrush