//
// Created by onelei on 2024/4/11.
//

#include "UpdateVBOSubDataHandler.h"
#include <GL/glew.h>
#include "../RenderPipeline.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void UpdateVBOSubDataHandler::Run() {
        RenderCommandHandler::Run();
        auto vbo = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetShader(vboHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, vertexData);
    }

    void UpdateVBOSubDataHandler::Clear() {
        RenderCommandHandler::Clear();
        free(vertexData);
        DivineBrush::ObjectPool<DivineBrush::UpdateVBOSubDataHandler>::Release(this);
    }
} // DivineBrush