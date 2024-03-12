//
// Created by onelei on 2024/3/8.
//

#include "shader.h"

namespace DivineBrush {

    Shader::Shader() {
        //创建顶点Shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        //指定Shader源码
        glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
        //编译Shader
        glCompileShader(vertex_shader);

        //创建片段Shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        //指定Shader源码
        glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
        //编译Shader
        glCompileShader(fragment_shader);

        //创建GPU程序
        program = glCreateProgram();
        //附加Shader
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        //Link
        glLinkProgram(program);

        //获取Shader中的变量
        mvp_location = glGetUniformLocation(program, "u_mvp");
        vpos_location = glGetAttribLocation(program, "a_pos");
        vcol_location = glGetAttribLocation(program, "a_color");
        a_uv_location = glGetAttribLocation(program, "a_uv");
        u_diffuse_texture_location= glGetUniformLocation(program, "u_diffuse_texture");
    }

    Shader::~Shader() {

    }
} // DivineBrush