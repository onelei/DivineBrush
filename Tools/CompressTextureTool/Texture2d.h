//
// Created by onelei on 2024/3/7.
//

#ifndef ENGINE_TEXTURE2D_H
#define ENGINE_TEXTURE2D_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "iostream"

namespace DivineBrush {

    class Texture2d {
    public:
        Texture2d();

        ~Texture2d();

    public:

        static Texture2d *LoadFile(const char *path);

        static void CompressFile(std::string imageFilePath, std::string targetImageFilePath);

        int GetWidth() const {
            return width;
        }

        int GetHeight() const {
            return height;
        }

        struct CompressFileHead {
            char type[3];
            int mipmapCount;
            int width;
            int height;
            int textureFormat;
            int compressSize;
        };

    private:
        GLint mipmapCount = 0;
        GLsizei width = 0;
        GLsizei height = 0;
        GLenum gl_texture_format;
        GLuint gl_texture_id = 0;
        unsigned int textureHandle = 0;
    };

} // DivineBrush

#endif //ENGINE_TEXTURE2D_H
