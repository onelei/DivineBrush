//
// Created by onelei on 2024/4/11.
//

#include "SetUniformMatrix4fvHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    SetUniformMatrix4fvHandler::SetUniformMatrix4fvHandler() {
        renderCommand = DivineBrush::RenderCommand::SetUniformMatrix4fv;
    }

    SetUniformMatrix4fvHandler::~SetUniformMatrix4fvHandler() {

    }

    void SetUniformMatrix4fvHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName), 1, transpose ? GL_TRUE : GL_FALSE,
                           &matrix[0][0]);
    }

    void SetUniformMatrix4fvHandler::Clear() {
        RenderCommandHandler::Clear();
        free(uniformName);
        DivineBrush::ObjectPool<DivineBrush::SetUniformMatrix4fvHandler>::Release(this);
    }
} // DivineBrush