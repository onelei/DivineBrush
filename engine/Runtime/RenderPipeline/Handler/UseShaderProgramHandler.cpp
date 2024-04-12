//
// Created by onelei on 2024/4/10.
//

#include "UseShaderProgramHandler.h"
#include "../RenderPipeline.h"

namespace DivineBrush {
    void UseShaderProgramHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetShader(shaderProgramHandle);
        glUseProgram(shaderProgram);
    }
} // DivineBrush