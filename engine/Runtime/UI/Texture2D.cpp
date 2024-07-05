//
// Created by onelei on 2024/3/7.
//

#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>
#include "Texture2D.h"
#include "../Application.h"
#include "../RenderPipeline/Handler/CreateCompressedTexImage2DHandler.h"
#include "../RenderPipeline/Handler/CreateTexImage2DHandler.h"
#include "../RenderPipeline/RenderGenerater.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    Texture2D::Texture2D() = default;

    Texture2D::~Texture2D() {
        if (textureHandle > 0) {
            RenderCommandBuffer::DeleteTexturesHandler(&textureHandle, 1);
        }
    }

    void Texture2D::LoadGLFWimage(const char *path, GLFWimage *image) {
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

    Texture2D *Texture2D::LoadFile(std::string path) {
        if (!std::filesystem::exists(path)){
            Debug::LogError("Texture2D::LoadFile Texture file not found: " + path);
            return nullptr;
        }
        // 加载图像
        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            return nullptr;
        }
        auto *texture2D = new Texture2D();
        // 根据颜色通道数设置OpenGL的格式
        int format = GL_RGB;
        if (channels == 1) {
            format = GL_ALPHA;
        } else if (channels == 3) {
            format = GL_RGB;
            texture2D->internalformat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
        } else if (channels == 4) {
            format = GL_RGBA;
            texture2D->internalformat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        }
        texture2D->width = width;
        texture2D->height = height;
        // 创建纹理
        glGenTextures(1, &(texture2D->gl_texture_id));
        glBindTexture(GL_TEXTURE_2D, texture2D->gl_texture_id);
        glTexImage2D(GL_TEXTURE_2D, texture2D->mipmapCount, texture2D->internalformat, texture2D->width,
                     texture2D->height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        return texture2D;
    }

    Texture2D *Texture2D::LoadCompressFile(const std::string& path) {
        auto *texture2D = new Texture2D();
        //读取 cpt 压缩纹理文件
        std::ifstream fileStream(Application::GetDataPath() + path, std::ios::in | std::ios::binary);
        CompressFileHead fileHead;
        fileStream.read((char *) &fileHead, sizeof(CompressFileHead));
        auto *data = (unsigned char *) malloc(fileHead.compressSize);
        fileStream.read((char *) data, fileHead.compressSize);
        fileStream.close();
        texture2D->width = fileHead.width;
        texture2D->height = fileHead.height;
        texture2D->internalformat = fileHead.internalformat;
        texture2D->textureHandle = RenderGenerater::CreateTexture();

        RenderCommandBuffer::CreateCompressedTexImage2DHandler(texture2D->textureHandle, texture2D->width,
                                                               texture2D->height, texture2D->internalformat,
                                                               fileHead.compressSize, data);

        free(data);
        return texture2D;
    }

    void Texture2D::CompressFile(std::string imageFilePath, std::string targetImageFilePath) {
        imageFilePath = Application::GetDataPath() + imageFilePath;
        stbi_set_flip_vertically_on_load(true);
        Texture2D *texture2D = LoadFile(imageFilePath.c_str());
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
        fileHead.mipmapCount = texture2D->mipmapCount;
        fileHead.width = texture2D->width;
        fileHead.height = texture2D->height;
        fileHead.internalformat = compressFormat;
        fileHead.compressSize = compressSize;

        fileStream.write((char *) &fileHead, sizeof(CompressFileHead));
        fileStream.write((char *) texture, compressSize);
        fileStream.close();
        free(texture);
        stbi_set_flip_vertically_on_load(false);
    }

    Texture2D *Texture2D::Create(unsigned short width, unsigned short height, unsigned int internalformat,
                                 unsigned int format, unsigned int data_type, unsigned char *data,
                                 unsigned int data_size) {
        auto texture2D = new Texture2D();
        texture2D->internalformat = internalformat;
        texture2D->width = width;
        texture2D->height = height;
        texture2D->textureHandle = RenderGenerater::CreateTexture();

        RenderCommandBuffer::CreateTexImage2DHandler(texture2D->textureHandle, texture2D->width, texture2D->height,
                                                     texture2D->internalformat, format, data_type, data,
                                                     data_size);

        return texture2D;
    }

    GLuint Texture2D::LoadGLTextureId(const char *path) {
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

    Texture2D *Texture2D::LoadFile(const aiTexture *aiTex, bool gama) {
        auto *texture2D = new Texture2D();
        int width, height, channels;
        unsigned char* data = nullptr;
        //FBX模型用stbi_load_form_memory加载
        if (aiTex->mHeight == 0)
        {
            data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData), aiTex->mWidth, &width, &height, &channels, 0);
        }
        else
        {
            data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData), aiTex->mWidth * aiTex->mHeight, &width, &height, &channels, 0);
        }
        if (data == nullptr) {
            std::cerr << "Failed to load texture from memory." << std::endl;
            return 0;
        }
//        std::ofstream outFile(fmt::format("texture_data{}.png", count++), std::ios::binary);
//        outFile.write(reinterpret_cast<const char*>(aiTex->pcData), aiTex->mWidth);
//        outFile.close();
        GLenum format;
        if (channels == 1) {
            format = GL_RED;
            texture2D->internalformat = GL_RED;
        } else if (channels == 3) {
            format = GL_RGB;
            texture2D->internalformat = gama ? GL_SRGB : GL_RGB;
        } else if (channels == 4) {
            format = GL_RGBA;
            texture2D->internalformat = gama ? GL_SRGB_ALPHA : GL_RGBA;
        }
        texture2D->width = width;
        texture2D->height = height;
        //1. 获取压缩是否成功
        GLint compressSuccess = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compressSuccess);

        //2. 获取压缩好的纹理数据尺寸
        GLint compressSize = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compressSize);

        //3. 获取具体的纹理压缩格式
        GLint compressFormat = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compressFormat);

        texture2D->internalformat = compressFormat;

        // 创建纹理
        glGenTextures(1, &(texture2D->gl_texture_id));
        glBindTexture(GL_TEXTURE_2D, texture2D->gl_texture_id);
        glTexImage2D(GL_TEXTURE_2D, texture2D->mipmapCount, texture2D->internalformat, texture2D->width,
                     texture2D->height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        texture2D->textureHandle = RenderGenerater::CreateTexture();
        RenderCommandBuffer::CreateCompressedTexImage2DHandler(texture2D->textureHandle, texture2D->width,
                                                               texture2D->height, texture2D->internalformat,
                                                               compressSize, data);
        
        delete []data;
        return texture2D;
    }


} // DivineBrush