//
// Created by onelei on 2024/4/11.
//

#include "GL/glew.h"
#include "SetStencilFuncHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetStencilFuncHandler::SetStencilFuncHandler() {
        renderCommand = DivineBrush::RenderCommand::SetStencilFunc;
    }

    SetStencilFuncHandler::~SetStencilFuncHandler(){

    }

    void SetStencilFuncHandler::Run() {
        RenderCommandHandler::Run();
        glStencilFunc(func, ref, mask);
    }

    void SetStencilFuncHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilFuncHandler>::Release(this);
    }
} // DivineBrush