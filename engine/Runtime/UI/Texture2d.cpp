//
// Created by onelei on 2024/3/7.
//

#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>
#include "Texture2d.h"
#include "../Application.h"
#include "../RenderPipeline/Handler/CreateCompressedTexImage2DHandler.h"
#include "../RenderPipeline/Handler/CreateTexImage2DHandler.h"
#include "../RenderPipeline/RenderGenerater.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    Texture2d::Texture2d() = default;

    Texture2d::~Texture2d() {
        if (textureHandle > 0) {
            RenderCommandBuffer::DeleteTexturesHandler(&textureHandle, 1);
        }
    }

    void Texture2d::LoadGLFWimage(const char *path, GLFWimage *image) {
        int width, height, channels;
        auto data = stbi_load(path, &width, &height, &channels, 4);
        if (data == nullptr) {
            return;
        }
        image->width = width;
        image->height = height;
        image->pixels = data;
        // 创建纹理
        GLuint gl_texture_id;
        glGenTextures(1, &gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, gl_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture2d *Texture2d::LoadFile(std::string path) {
        if (!std::filesystem::exists(path)){
            Debug::LogError("Texture2d::LoadFile Texture file not found: " + path);
            return nullptr;
        }
        // 加载图像
        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            return nullptr;
        }
        auto *pTexture2D = new Texture2d();
        // 根据颜色通道数设置OpenGL的格式
        int image_data_format = GL_RGB;
        if (channels == 1) {
            image_data_format = GL_ALPHA;
        } else if (channels == 3) {
            image_data_format = GL_RGB;
            pTexture2D->gl_texture_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
        } else if (channels == 4) {
            image_data_format = GL_RGBA;
            pTexture2D->gl_texture_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        }
        pTexture2D->width = width;
        pTexture2D->height = height;
        // 创建纹理
        glGenTextures(1, &(pTexture2D->gl_texture_id));
        glBindTexture(GL_TEXTURE_2D, pTexture2D->gl_texture_id);
        glTexImage2D(GL_TEXTURE_2D, pTexture2D->mipmapCount, pTexture2D->gl_texture_format, pTexture2D->width,
                     pTexture2D->height,
                     0, image_data_format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        return pTexture2D;
    }

    Texture2d *Texture2d::LoadCompressFile(std::string path) {
        auto *texture2d = new Texture2d();
        //读取 cpt 压缩纹理文件
        std::ifstream fileStream(Application::GetDataPath() + path, std::ios::in | std::ios::binary);
        CompressFileHead fileHead;
        fileStream.read((char *) &fileHead, sizeof(CompressFileHead));
        auto *data = (unsigned char *) malloc(fileHead.compressSize);
        fileStream.read((char *) data, fileHead.compressSize);
        fileStream.close();
        texture2d->width = fileHead.width;
        texture2d->height = fileHead.height;
        texture2d->gl_texture_format = fileHead.textureFormat;
        texture2d->textureHandle = RenderGenerater::CreateTexture();

        RenderCommandBuffer::CreateCompressedTexImage2DHandler(texture2d->textureHandle, texture2d->width,
                                                               texture2d->height, texture2d->gl_texture_format,
                                                               fileHead.compressSize, data);

        free(data);
        return texture2d;
    }

    void Texture2d::CompressFile(std::string imageFilePath, std::string targetImageFilePath) {
        imageFilePath = Application::GetDataPath() + imageFilePath;
        stbi_set_flip_vertically_on_load(true);
        Texture2d *texture2d = LoadFile(imageFilePath.c_str());
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
        std::ofstream fileStream(Application::GetDataPath() + targetImageFilePath, std::ios::out | std::ios::binary);

        CompressFileHead fileHead;
        //glCompressedTexImage2D -> glt
        fileHead.type[0] = 'c';
        fileHead.type[1] = 'p';
        fileHead.type[2] = 't';
        fileHead.mipmapCount = texture2d->mipmapCount;
        fileHead.width = texture2d->width;
        fileHead.height = texture2d->height;
        fileHead.textureFormat = compressFormat;
        fileHead.compressSize = compressSize;

        fileStream.write((char *) &fileHead, sizeof(CompressFileHead));
        fileStream.write((char *) texture, compressSize);
        fileStream.close();
        free(texture);
        stbi_set_flip_vertically_on_load(false);
    }

    Texture2d *Texture2d::Create(unsigned short width, unsigned short height, unsigned int server_format,
                                 unsigned int client_format, unsigned int data_type, unsigned char *data,
                                 unsigned int data_size) {
        auto texture2d = new Texture2d();
        texture2d->gl_texture_format = server_format;
        texture2d->width = width;
        texture2d->height = height;
        texture2d->textureHandle = RenderGenerater::CreateTexture();

        RenderCommandBuffer::CreateTexImage2DHandler(texture2d->textureHandle, texture2d->width, texture2d->height,
                                                     texture2d->gl_texture_format, client_format, data_type, data,
                                                     data_size);

        return texture2d;
    }

    GLuint Texture2d::LoadGLTextureId(const char *path) {
        int width, height, channels;
        auto data = stbi_load(path, &width, &height, &channels, 4);
        if (data == nullptr) {
            return 0;
        }

        // 创建纹理
        GLuint gl_texture_id;
        glGenTextures(1, &gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, gl_texture_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return gl_texture_id;
    }


} // DivineBrush