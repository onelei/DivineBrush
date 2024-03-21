//
// Created by onelei on 2024/3/7.
//

#include <iostream>
#include <fstream>
#include "texture2d.h"
#include "../../application.h"

namespace DivineBrush {
    static const unsigned int bytesPerPixel = 4;

    Texture2d::Texture2d() = default;

    Texture2d::~Texture2d() = default;

    void Texture2d::LoadGLFWimage(const char *path, GLFWimage *image) {
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType( path);
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
            return;
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
        image->pixels = new BYTE[size];
        memcpy(image->pixels, bytes, size);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        FreeImage_Unload(bitmap32);
    }

    Texture2d *Texture2d::LoadFile(const char *path) {
        auto *pTexture2D = new Texture2d();
        // 图像格式
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);
        if (format == FIF_UNKNOWN) {
            format = FreeImage_GetFIFFromFilename(path);
            if (format == FIF_UNKNOWN) {
                // 无法识别图像格式
                std::cerr << "Could not get image format : " << path << std::endl;
                return nullptr;
            }
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
        // 检查像素格式决定是否有Alpha通道
        auto bitsPerPixel = FreeImage_GetBPP(bitmap32);
        bool hasAlpha = FreeImage_IsTransparent(bitmap32) || (bitsPerPixel == 32);
        GLenum gl_texture_format = hasAlpha ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
        //如果原始图像数据是以BGR(A)格式存储的（FreeImage的常规情形），而上传时没有正确地转换为OpenGL期望的RGB(A)格式，会导致颜色通道位置错误，从而产生色彩偏差。
        // 对于DXT压缩，错误的通道顺序会导致颜色混乱。
        int texture_format = hasAlpha ? GL_BGRA : GL_BGR;
        pTexture2D->width = static_cast<GLsizei>(FreeImage_GetWidth(bitmap32));
        pTexture2D->height = static_cast<GLsizei>(FreeImage_GetHeight(bitmap32));
        pTexture2D->gl_texture_format = gl_texture_format;
        // 创建纹理
        glGenTextures(1, &(pTexture2D->gl_texture_id));
        glBindTexture(GL_TEXTURE_2D, pTexture2D->gl_texture_id);
        glTexImage2D(GL_TEXTURE_2D, pTexture2D->mipmapCount, pTexture2D->gl_texture_format, pTexture2D->width,
                     pTexture2D->height,
                     0, texture_format, GL_UNSIGNED_BYTE, FreeImage_GetBits(bitmap32));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        FreeImage_Unload(bitmap32);
        return pTexture2D;
    }

    Texture2d *Texture2d::LoadCompressFile(std::string &path) {
        auto *pTexture2D = new Texture2d();
        //读取 cpt 压缩纹理文件
        std::ifstream fileStream(Application::GetDataPath()+path, std::ios::in | std::ios::binary);
        CompressFileHead fileHead;
        fileStream.read((char *) &fileHead, sizeof(CompressFileHead));
        auto *data = (unsigned char *) malloc(fileHead.compressSize);
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        delete (data);
        return pTexture2D;
    }

    void Texture2d::CompressFile(std::string &imageFilePath, std::string &targetImageFilePath) {
        Texture2d *texture2d = LoadFile(imageFilePath.c_str());
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
        std::ofstream fileStream(Application::GetDataPath()+targetImageFilePath, std::ios::out | std::ios::binary);

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

    Texture2d *Texture2d::Create(unsigned short width, unsigned short height, unsigned int server_format,
                                 unsigned int client_format, unsigned int data_type, unsigned char *data) {
        auto texture2d = new Texture2d();
        texture2d->gl_texture_format = server_format;
        texture2d->width = width;
        texture2d->height = height;

        //1. 通知显卡创建纹理对象，返回句柄;
        glGenTextures(1, &(texture2d->gl_texture_id));
        //2. 将纹理绑定到特定纹理目标;
        glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id);
        //3. 将图片rgb数据上传到GPU;
        glTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format, texture2d->width, texture2d->height, 0,
                     client_format, data_type, data);
        //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        return texture2d;
    }
} // DivineBrush