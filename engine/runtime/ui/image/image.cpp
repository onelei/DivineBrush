//
// Created by onelei on 2024/2/29.
//

#include <iostream>
#include "image.h"
#include "../../template/dynamic_array_pool.h"

namespace DivineBrush::UI {
    static int bytesPerPixel = 4; // 通常是RGBA，所以是4字节
    static DynamicArrayPool<unsigned char> pool;

    Image::Image() : width(0), height(0), pixels(nullptr) {

    }

    Image::~Image() {
        if (this->pixels != nullptr) {
            free(this->pixels);
        }
    }

    Image *Image::LoadImage(char *filename) {
        auto *image = new Image();
        //FreeImage_Initialise();
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename);
        if (format == -1) {
            std::cerr << "Could not find image: " << filename << std::endl;
            return nullptr;
        }

        // 加载图像
        FIBITMAP *bitmap = FreeImage_Load(format, filename);
        if (!bitmap) {
            std::cerr << "Failed to load image: " << filename << std::endl;
            return nullptr;
        }

        // 转换为32位RGB图像
        FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(bitmap);

        auto width = FreeImage_GetWidth(bitmap32);
        auto height = FreeImage_GetHeight(bitmap32);
        auto size = width * height * bytesPerPixel;
        image->width = FreeImage_GetWidth(bitmap32);
        image->height = FreeImage_GetHeight(bitmap32);
        image->pixels = new BYTE[size];
        FlipImageVertically(width, height, size, FreeImage_GetBits(bitmap32), image->pixels);

        FreeImage_Unload(bitmap32);
        //FreeImage_DeInitialise();
        return image;
    }

    GLuint Image::LoadImageToTextureID(char *filename) {
        FreeImage_Initialise();
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename);
        if (format == -1) {
            std::cout << "Could not find image: " << filename << std::endl;
            return 0;
        }

        // 加载图像
        FIBITMAP *bitmap = FreeImage_Load(format, filename);
        if (!bitmap) {
            std::cout << "Failed to load image: " << filename << std::endl;
            return 0;
        }

        // 转换为32位RGB图像
        FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(bitmap);

        auto width = FreeImage_GetWidth(bitmap32);
        auto height = FreeImage_GetHeight(bitmap32);
        auto size = width * height * bytesPerPixel;
        auto *flippedPixels = pool.Get(size);
        FlipImageVertically(width, height, size, FreeImage_GetBits(bitmap32), flippedPixels);
        // 创建纹理
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_BGRA, GL_UNSIGNED_BYTE, (void *) flippedPixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        FreeImage_Unload(bitmap32);
        FreeImage_DeInitialise();
        pool.Release(flippedPixels, size);
        return textureID;
    }

    void Image::FlipImageVertically(Image *image) {
        auto size = image->width * image->height * bytesPerPixel;
        auto *flippedPixels = pool.Get(size);
        FlipImageVertically(image->width, image->height, size, flippedPixels, image->pixels);
        pool.Release(flippedPixels, size);
    }

    void Image::FlipImageVertically(unsigned int width, unsigned int height, unsigned int size, BYTE *pixels,
                                    BYTE *flippedPixels) {
        for (int y = 0; y < height; y++) {
            memcpy(flippedPixels + (height - y - 1) * width * bytesPerPixel,
                   pixels + y * width * bytesPerPixel,
                   width * bytesPerPixel);
        }
        memcpy(pixels, flippedPixels, size);
    }
} // DivineBrush