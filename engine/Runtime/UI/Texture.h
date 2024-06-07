//
// Created by onelei on 2024/3/7.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

//order is important
#include <GL/glew.h>
#include <GL/gl.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
//order is important
#include "../Component/Object.h"

namespace DivineBrush {
    class Texture : public Object {
    public:
        Texture();

        ~Texture();

        unsigned int GetTextureHandle() {
            return textureHandle;
        }

        GLuint GetTextureID() {
            return gl_texture_id;
        }

    protected:
        GLint mipmapCount = 0;
        GLsizei width = 0;
        GLsizei height = 0;
        GLenum gl_texture_format;
        GLuint gl_texture_id = 0;
        unsigned int textureHandle = 0;
    };
}// DivineBrush

#endif //ENGINE_TEXTURE_H
