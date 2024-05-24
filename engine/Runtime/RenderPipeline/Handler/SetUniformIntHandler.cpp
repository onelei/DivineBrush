//
// Created by onelei on 2024/4/11.
//

#include "SetUniformIntHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    SetUniformIntHandler::SetUniformIntHandler() {
        renderCommand = DivineBrush::RenderCommand::SetUniformInt;
    }

    SetUniformIntHandler::~SetUniformIntHandler() {

    }

    void SetUniformIntHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        auto u_texture_location = glGetUniformLocation(shaderProgram, uniformName);
        glUniform1i(u_texture_location, value);
    }

    void SetUniformIntHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniformIntHandler>::Release(this);
    }
} // DivineBrush