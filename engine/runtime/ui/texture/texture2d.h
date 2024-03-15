//
// Created by onelei on 2024/3/7.
//

#ifndef ENGINE_TEXTURE2D_H
#define ENGINE_TEXTURE2D_H

#include "texture.h"
#include "iostream"

namespace DivineBrush {

    class Texture2d : public Texture {
    public:
        Texture2d();

        ~Texture2d();

    public:
        static void LoadGLFWimage(const char *path, GLFWimage *image);

        static Texture2d *LoadFile(const char *path);

        static Texture2d *LoadCompressFile(std::string &path);

        static void CompressFile(std::string &imageFilePath, std::string &targetImageFilePath);

        struct CompressFileHead {
            char type[3];
            int mipmapCount;
            int width;
            int height;
            int textureFormat;
            int compressSize;
        };
    };

} // DivineBrush

#endif //ENGINE_TEXTURE2D_H
