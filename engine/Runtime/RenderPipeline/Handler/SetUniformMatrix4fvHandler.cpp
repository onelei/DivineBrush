//
// Created by onelei on 2024/4/11.
//

#include "SetUniformMatrix4fvHandler.h"
#include "../RenderPipeline.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetUniformMatrix4fvHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetShader(shaderProgramHandle);
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName), 1, transpose ? GL_TRUE : GL_FALSE,
                           &matrix[0][0]);
    }

    void SetUniformMatrix4fvHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniformMatrix4fvHandler>::Release(this);
    }
} // DivineBrush