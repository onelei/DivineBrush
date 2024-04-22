//
// Created by onelei on 2024/4/11.
//

#include "GL/glew.h"
#include "SetBlendFuncHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetBlendFuncHandler::SetBlendFuncHandler() {
        renderCommand = DivineBrush::RenderCommand::SetBlendFunc;
    }

    SetBlendFuncHandler::~SetBlendFuncHandler() {

    }

    void SetBlendFuncHandler::Run() {
        RenderCommandHandler::Run();
        glBlendFunc(sFactor, dFactor);
    }

    void SetBlendFuncHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetBlendFuncHandler>::Release(this);
    }
} // DivineBrush