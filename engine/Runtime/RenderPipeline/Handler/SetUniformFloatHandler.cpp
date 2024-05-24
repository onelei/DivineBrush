//
// Created by onelei on 2024/5/24.
//

#include "SetUniformFloatHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    SetUniformFloatHandler::SetUniformFloatHandler() {
        renderCommand = DivineBrush::RenderCommand::SetUniformFloat;
    }

    SetUniformFloatHandler::~SetUniformFloatHandler() {

    }

    void SetUniformFloatHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        auto u_texture_location = glGetUniformLocation(shaderProgram, uniformName);
        glUniform1f(u_texture_location, value);
    }

    void SetUniformFloatHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniformFloatHandler>::Release(this);
    }
} // DivineBrush