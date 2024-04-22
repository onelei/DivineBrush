//
// Created by onelei on 2024/4/11.
//

#include "GL/glew.h"
#include "SetStencilOpHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetStencilOpHandler::SetStencilOpHandler() {
        renderCommand = DivineBrush::RenderCommand::SetStencilOp;
    }

    SetStencilOpHandler::~SetStencilOpHandler() {

    }

    void SetStencilOpHandler::Run() {
        RenderCommandHandler::Run();
        glStencilOp(fail, zFail, zPass);
    }

    void SetStencilOpHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilOpHandler>::Release(this);
    }
} // DivineBrush