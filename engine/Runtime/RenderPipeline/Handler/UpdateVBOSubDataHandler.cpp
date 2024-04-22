//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "UpdateVBOSubDataHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    UpdateVBOSubDataHandler::UpdateVBOSubDataHandler() {
        renderCommand = DivineBrush::RenderCommand::UpdateVBOSubData;
    }

    UpdateVBOSubDataHandler::~UpdateVBOSubDataHandler() {

    }

    void UpdateVBOSubDataHandler::Run() {
        RenderCommandHandler::Run();
        auto vbo = RenderGenerater::GetShader(vboHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, vertexData);
    }

    void UpdateVBOSubDataHandler::Clear() {
        RenderCommandHandler::Clear();
        free(vertexData);
        DivineBrush::ObjectPool<DivineBrush::UpdateVBOSubDataHandler>::Release(this);
    }
} // DivineBrush