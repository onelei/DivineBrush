//
// Created by onelei on 2024/3/7.
//

#ifndef ENGINE_TEXTURE2D_H
#define ENGINE_TEXTURE2D_H

#include <assimp/texture.h>
#include "Texture.h"
#include "iostream"

namespace DivineBrush {

    class Texture2D : public Texture {
    public:
        Texture2D();

        ~Texture2D();

    public:
        static void LoadGLFWimage(const char *path, GLFWimage *image);

        static GLuint LoadGLTextureId(const char *path);

        static Texture2D *LoadFile(std::string path);

        static Texture2D *LoadCompressFile(const std::string& path);

        static void CompressFile(std::string imageFilePath, std::string targetImageFilePath);

        static Texture2D *Create(unsigned short width, unsigned short height, unsigned int internalformat,
                                 unsigned int format, unsigned int data_type, unsigned char *data,
                                 unsigned int data_size);

        static Texture2D *LoadFile(const aiTexture *aiTex, bool gama);

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
            int internalformat;
            int compressSize;
        };

    private:
        int width = 0;
        int height = 0;
    };

} // DivineBrush

#endif //ENGINE_TEXTURE2D_H
