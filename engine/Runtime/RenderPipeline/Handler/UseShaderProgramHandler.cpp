//
// Created by onelei on 2024/4/10.
//

#include "UseShaderProgramHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {

    UseShaderProgramHandler::UseShaderProgramHandler() {
        renderCommand = DivineBrush::RenderCommand::UseShaderProgram;
    }

    UseShaderProgramHandler::~UseShaderProgramHandler() {

    }

    void UseShaderProgramHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgram = RenderGenerater::GetShader(shaderProgramHandle);
        glUseProgram(shaderProgram);
    }

    void UseShaderProgramHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::UseShaderProgramHandler>::Release(this);
    }
} // DivineBrush