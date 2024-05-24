//
// Created by onelei on 2024/5/24.
//

#include "SetUniformVector3Handler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    SetUniformVector3Handler::SetUniformVector3Handler() {
        renderCommand = DivineBrush::RenderCommand::SetUniformVector3;
    }

    SetUniformVector3Handler::~SetUniformVector3Handler() {

    }

    void SetUniformVector3Handler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        auto u_texture_location = glGetUniformLocation(shaderProgram, uniformName);
        glUniform3f(u_texture_location, value.x, value.y, value.z);
    }

    void SetUniformVector3Handler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniformVector3Handler>::Release(this);
    }
} // DivineBrush