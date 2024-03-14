//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace DivineBrush {
    static const char* vertex_shader_text =
            "#version 330 core\n"

            "uniform mat4 u_mvp;\n"

            "layout(location = 0) in  vec3 a_pos;\n"
            "layout(location = 1) in  vec4 a_color;\n"
            "layout(location = 2) in  vec2 a_uv;\n"

            "out vec4 v_color;\n"
            "out vec2 v_uv;\n"

            "void main()\n"
            "{\n"
            "    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
            "    v_color = a_color;\n"
            "    v_uv = a_uv;\n"
            "}\n";

    static const char* fragment_shader_text =
            "#version 330 core\n"
            "uniform sampler2D u_diffuse_texture;"
            "in vec4 v_color;\n"
            "in vec2 v_uv;\n"
            "layout(location = 0) out vec4 o_fragColor;\n"
            "void main()\n"
            "{\n"
            "    o_fragColor = texture(u_diffuse_texture,v_uv) * v_color;\n"
            "}\n";



    class Shader {
    public:
        Shader();

        ~Shader();

        GLuint vertex_shader, fragment_shader, program;
        GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location, a_uv_location;
        GLuint kVBO,kEBO;
        GLuint kVAO;
    };

} // DivineBrush

#endif //ENGINE_SHADER_H
