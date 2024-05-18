//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "UpdateVBODataHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    UpdateVBODataHandler::UpdateVBODataHandler() {
        renderCommand = DivineBrush::RenderCommand::UpdateVBOData;
    }

    UpdateVBODataHandler::~UpdateVBODataHandler() {

    }

    void UpdateVBODataHandler::Run() {
        RenderCommandHandler::Run();
        auto vbo = RenderGenerater::GetShader(vboHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, vertexData);
    }

    void UpdateVBODataHandler::Clear() {
        RenderCommandHandler::Clear();
        free(vertexData);
        DivineBrush::ObjectPool<DivineBrush::UpdateVBODataHandler>::Release(this);
    }
} // DivineBrush