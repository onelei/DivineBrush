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

namespace DivineBrush {
    static const char* vertex_shader_text =
            "#version 110\n"

            "uniform mat4 u_mvp;\n"

            "attribute  vec3 a_pos;\n"
            "attribute  vec4 a_color;\n"
            "attribute  vec2 a_uv;\n"

            "varying vec4 v_color;\n"
            "varying vec2 v_uv;\n"

            "void main()\n"
            "{\n"
            "    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
            "    v_color = a_color;\n"
            "    v_uv = a_uv;\n"
            "}\n";

    static const char* fragment_shader_text =
            "#version 110\n"
            "uniform sampler2D u_diffuse_texture;"
            "varying vec4 v_color;\n"
            "varying vec2 v_uv;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = texture2D(u_diffuse_texture,v_uv);\n"
            "}\n";

    static const glm::vec3 kPositions[36] =
            {
                    //Front
                    glm::vec3(-1.0f, -1.0f, 1.0f),
                    glm::vec3(1.0f, -1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),

                    glm::vec3(-1.0f, -1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(-1.0f, 1.0f, 1.0f),

                    //back
                    glm::vec3(1.0f, -1.0f, -1.0f),
                    glm::vec3(-1.0f, -1.0f, -1.0f),
                    glm::vec3(-1.0f, 1.0f, -1.0f),

                    glm::vec3(1.0f, -1.0f, -1.0f),
                    glm::vec3(-1.0f, 1.0f, -1.0f),
                    glm::vec3(1.0f, 1.0f, -1.0f),

                    //left
                    glm::vec3(-1.0f, -1.0f, -1.0f),
                    glm::vec3(-1.0f, -1.0f, 1.0f),
                    glm::vec3(-1.0f, 1.0f, 1.0f),

                    glm::vec3(-1.0f, -1.0f, -1.0f),
                    glm::vec3(-1.0f, 1.0f, 1.0f),
                    glm::vec3(-1.0f, 1.0f, -1.0f),

                    //right
                    glm::vec3(1.0f, -1.0f, 1.0f),
                    glm::vec3(1.0f, -1.0f, -1.0f),
                    glm::vec3(1.0f, 1.0f, -1.0f),

                    glm::vec3(1.0f, -1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, -1.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),

                    //up
                    glm::vec3(-1.0f, 1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, -1.0f),

                    glm::vec3(-1.0f, 1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, -1.0f),
                    glm::vec3(-1.0f, 1.0f, -1.0f),

                    //down
                    glm::vec3(-1.0f, -1.0f, -1.0f),
                    glm::vec3(1.0f, -1.0f, -1.0f),
                    glm::vec3(1.0f, -1.0f, 1.0f),

                    glm::vec3(-1.0f, -1.0f, -1.0f),
                    glm::vec3(1.0f, -1.0f, 1.0f),
                    glm::vec3(-1.0f, -1.0f, 1.0f),
            };

    static const glm::vec4 kColors[36] =
            {
                    //Front
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),

                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),

                    //back
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),

                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),
                    glm::vec4(1, 0, 0, 1),

                    //left
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),

                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),

                    //right
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),

                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),
                    glm::vec4(0, 1, 0, 1),

                    //up
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),

                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),

                    //down
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),

                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),
                    glm::vec4(0, 0, 1, 1),
            };

    static const glm::vec2 kUvs[36] =
            {
                    //Front
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    //back
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    //left
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    //right
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    //up
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    //down
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),

                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),
            };

    class Shader {
    public:
        Shader();

        ~Shader();

        GLuint vertex_shader, fragment_shader, program;
        GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location, a_uv_location;
    };

} // DivineBrush

#endif //ENGINE_SHADER_H
