//
// Created by onelei on 2024/4/10.
//

#include "CreateCompressedTexImage2DHandler.h"
#include <GL/glew.h>
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    CreateCompressedTexImage2DHandler::CreateCompressedTexImage2DHandler() {
        renderCommand = DivineBrush::RenderCommand::CreateCompressedTexImage2D;
    }

    CreateCompressedTexImage2DHandler::~CreateCompressedTexImage2DHandler() {

    }

    void CreateCompressedTexImage2DHandler::Run() {
        RenderCommandHandler::Run();
        // 创建纹理
        GLuint gl_texture_id;
        glGenTextures(1, &gl_texture_id);
        glBindTexture(GL_TEXTURE_2D, gl_texture_id);
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, compressSize, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        free(data);
        RenderGenerater::SetTexture(textureHandle, gl_texture_id);
    }

    void CreateCompressedTexImage2DHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::CreateCompressedTexImage2DHandler>::Release(this);
    }
} // DivineBrush