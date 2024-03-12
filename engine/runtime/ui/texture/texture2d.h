//
// Created by onelei on 2024/3/7.
//

#ifndef ENGINE_TEXTURE2D_H
#define ENGINE_TEXTURE2D_H

#include "texture.h"

namespace DivineBrush {

    class Texture2d : public Texture {
    public:
        Texture2d();

        ~Texture2d();

    public:
        static void LoadGLFWimage(char *path, GLFWimage *image);

        static Texture2d *LoadFile(char *path);

        static Texture2d *LoadCompressFile(char *path);

        static void CompressFile(char *imageFilePath, char *targetImageFilePath);

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
