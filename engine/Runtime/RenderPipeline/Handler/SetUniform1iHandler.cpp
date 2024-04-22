//
// Created by onelei on 2024/4/11.
//

#include "SetUniform1iHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    SetUniform1iHandler::SetUniform1iHandler() {
        renderCommand = DivineBrush::RenderCommand::SetUniform1i;
    }

    SetUniform1iHandler::~SetUniform1iHandler() {

    }

    void SetUniform1iHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        auto u_texture_location = glGetUniformLocation(shaderProgram, uniformName);
        glUniform1i(u_texture_location, value);
    }

    void SetUniform1iHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniform1iHandler>::Release(this);
    }
} // DivineBrush