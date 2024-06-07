//
// Created by onelei on 2024/3/7.
//

#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture2d.h"

namespace DivineBrush {
    Texture2d::Texture2d() = default;

    Texture2d::~Texture2d() {

    }

    Texture2d *Texture2d::LoadFile(const char *path) {
        // 加载图像
        int width, height, channels;
        auto data = stbi_load(path, &width, &height, &channels, 0);
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

    void Texture2d::CompressFile(std::string imageFilePath, std::string targetImageFilePath) {
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

        fileStream.write((char *) &fileHead, sizeof(CompressFileHead));
        fileStream.write((char *) texture, compressSize);
        fileStream.close();
        free(texture);
        stbi_set_flip_vertically_on_load(false);
    }

} // DivineBrush