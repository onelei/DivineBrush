//
// Created by onelei on 2024/3/7.
//

#include <iostream>
#include <fstream>
#include "texture2d.h"
#include "../../../depends/time/stop_watch.h"

namespace DivineBrush {
    static const unsigned int bytesPerPixel = 4;

    Texture2d::Texture2d() {

    }

    Texture2d::~Texture2d() {

    }

    void Texture2d::LoadGLFWimage(char *path, GLFWimage* image) {
        //FreeImage_Initialise();
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);
        if (format == -1) {
            std::cerr << "Could not find pTexture2D: " << path <<
                      std::endl;
            return;
        }
        // 加载图像
        FIBITMAP *bitmap = FreeImage_Load(format, path);
        if (!bitmap) {
            std::cerr << "Failed to load pTexture2D: " << path << std::endl;
            return;
        }

        // 转换为32位RGB图像
        FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(bitmap);
        if (!FreeImage_FlipVertical(bitmap32)) {
            std::cerr << "Failed to flip vertical pTexture2D: " << path << std::endl;
            return ;
        }

        auto width = FreeImage_GetWidth(bitmap32);
        auto height = FreeImage_GetHeight(bitmap32);
        auto size = width * height * bytesPerPixel;
        image->width = static_cast<GLsizei>(width);
        image->height = static_cast<GLsizei>(height);
        // 创建纹理
        GLuint gl_texture_id;
        glGenTextures(1, &gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, gl_texture_id);

        auto bytes = FreeImage_GetBits(bitmap32);
        image->pixels = new BYTE [size];
        memcpy(image->pixels, bytes, size);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        FreeImage_Unload(bitmap32);
    }

    Texture2d *Texture2d::LoadFile(char *path) {
        auto *pTexture2D = new Texture2d();
        //FreeImage_Initialise();
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);
        if (format == -1) {
            std::cerr << "Could not find pTexture2D: " << path << std::endl;
            return nullptr;
        }
        // 加载图像
        FIBITMAP *bitmap = FreeImage_Load(format, path);
        if (!bitmap) {
            std::cerr << "Failed to load pTexture2D: " << path << std::endl;
            return nullptr;
        }

        // 转换为32位RGB图像
        FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(bitmap);
        if (!FreeImage_FlipVertical(bitmap32)) {
            std::cerr << "Failed to flip vertical pTexture2D: " << path << std::endl;
            return nullptr;
        }

        auto width = FreeImage_GetWidth(bitmap32);
        auto height = FreeImage_GetHeight(bitmap32);
        auto size = width * height * bytesPerPixel;
//        FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(bitmap);
//        switch (colorType) {
//            //灰度图，光亮度低的地方显示为白色，可以使用单一颜色通道在OpenGL中表示灰度值。
//            case FIC_MINISWHITE:
//                //灰度图，光亮度低的地方显示为黑色，同样用单一颜色通道在OpenGL中表示灰度值。
//            case FIC_MINISBLACK:
//                pTexture2D->gl_texture_format = GL_RED;
//                break;
//                //传统的RGB颜色模型，使用三个颜色通道，不包含透明度。
//            case FIC_RGB:
//                pTexture2D->gl_texture_format = GL_RGB;
//                break;
//                //RGB颜色模型带有alpha透明通道，使用四个颜色通道。
//            case FIC_RGBALPHA:
//                pTexture2D->gl_texture_format = GL_RGBA;
//                break;
//                //调色板索引色图像，在GL中直接使用调色板索引模型较为复杂，一般不直接映射，而是先转换成RGB或RGBA格式。
//            case FIC_PALETTE:
//                //CMYK颜色模型主要用于打印，在OpenGL中不直接使用。一般需要将CMYK转换为RGB或RGBA格式进行处理。
//            case FIC_CMYK:
//            default:
//                break;
//        }
        pTexture2D->width = static_cast<GLsizei>(FreeImage_GetWidth(bitmap32));
        pTexture2D->height = static_cast<GLsizei>(FreeImage_GetHeight(bitmap32));
        pTexture2D->gl_texture_format = GL_BGRA;
        // 创建纹理
        glGenTextures(1, &pTexture2D->gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, pTexture2D->gl_texture_id);


        glTexImage2D(GL_TEXTURE_2D, pTexture2D->mipmapCount, GL_COMPRESSED_RGB, pTexture2D->width, pTexture2D->height,
                     0, pTexture2D->gl_texture_format, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap32));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        FreeImage_Unload(bitmap32);
        //FreeImage_DeInitialise();
        return pTexture2D;
    }

    Texture2d *Texture2d::LoadCompressFile(char *path) {
        auto *pTexture2D = new Texture2d();
        StopWatch stopwatch;
        stopwatch.Start();
        //读取 cpt 压缩纹理文件
        std::ifstream fileStream(path, std::ios::in | std::ios::binary);
        CompressFileHead fileHead;
        fileStream.read((char *) &fileHead, sizeof(CompressFileHead));
        unsigned char *data = (unsigned char *) malloc(fileHead.compressSize);
        fileStream.read((char *) data, fileHead.compressSize);
        fileStream.close();

        pTexture2D->width = fileHead.width;
        pTexture2D->height = fileHead.height;
        pTexture2D->gl_texture_format = fileHead.textureFormat;
        // 创建纹理
        glGenTextures(1, &pTexture2D->gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, pTexture2D->gl_texture_id);
        glCompressedTexImage2D(GL_TEXTURE_2D, pTexture2D->mipmapCount, pTexture2D->gl_texture_format, pTexture2D->width,
                               pTexture2D->height,
                               0, fileHead.compressSize, data);
        stopwatch.Stop();
        auto time = stopwatch.ElapsedMilliSeconds();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        delete (data);
        return pTexture2D;
    }

    void Texture2d::CompressFile(char *imageFilePath, char *targetImageFilePath) {

        Texture2d *texture2d = LoadFile(imageFilePath);
        if (texture2d == nullptr) {
            std::cerr << "Failed to load pTexture2D: " << imageFilePath << std::endl;
            return;
        }

        //1. 获取压缩是否成功
        GLint compressSuccess = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compressSuccess);

        //2. 获取压缩好的纹理数据尺寸
        GLint compressSize = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compressSize);

        //3. 获取具体的纹理压缩格式
        GLint compressFormat = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compressFormat);

        //4. 从GPU中，将显存中保存的压缩好的纹理数据，下载到内存
        void *texture = malloc(compressSize);
        glGetCompressedTexImage(GL_TEXTURE_2D, 0, texture);

        //5. 保存为文件
        std::ofstream fileStream(targetImageFilePath, std::ios::out | std::ios::binary);

        CompressFileHead fileHead;
        //glCompressedTexImage2D -> glt
        fileHead.type[0] = 'g';
        fileHead.type[1] = 'l';
        fileHead.type[2] = 't';
        fileHead.mipmapCount = texture2d->mipmapCount;
        fileHead.width = texture2d->width;
        fileHead.height = texture2d->height;
        fileHead.textureFormat = compressFormat;
        fileHead.compressSize = compressSize;

        fileStream.write((char *) &fileHead, sizeof(fileHead));
        fileStream.write((char *) texture, compressSize);
        fileStream.close();
    }
} // DivineBrush