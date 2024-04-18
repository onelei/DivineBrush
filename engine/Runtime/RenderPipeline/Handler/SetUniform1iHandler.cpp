//
// Created by onelei on 2024/4/11.
//

#include "SetUniform1iHandler.h"
#include "../RenderPipeline.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetUniform1iHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetShader(shaderProgramHandle);
        auto u_texture_location = glGetUniformLocation(shaderProgram, uniformName);
        glUniform1i(u_texture_location, value);
    }

    void SetUniform1iHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniform1iHandler>::Release(this);
    }
} // DivineBrush