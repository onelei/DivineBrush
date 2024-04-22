//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "UpdateTextureSubImage2DHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    UpdateTextureSubImage2DHandler::UpdateTextureSubImage2DHandler() {
        renderCommand = DivineBrush::RenderCommand::UpdateTextureSubImage2D;
    }

    UpdateTextureSubImage2DHandler::~UpdateTextureSubImage2DHandler() {

    }

    void UpdateTextureSubImage2DHandler::Run() {
        RenderCommandHandler::Run();

        auto textureId = RenderGenerater::GetTexture(textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, format, type, data);
    }

    void UpdateTextureSubImage2DHandler::Clear() {
        RenderCommandHandler::Clear();
        free(data);
        DivineBrush::ObjectPool<DivineBrush::UpdateTextureSubImage2DHandler>::Release(this);
    }
} // DivineBrush