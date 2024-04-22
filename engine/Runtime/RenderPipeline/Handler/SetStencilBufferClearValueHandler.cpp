//
// Created by onelei on 2024/4/11.
//

#include "GL/glew.h"
#include "SetStencilBufferClearValueHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetStencilBufferClearValueHandler::SetStencilBufferClearValueHandler() {
        renderCommand = DivineBrush::RenderCommand::SetStencilBufferClearValue;
    }

    SetStencilBufferClearValueHandler::~SetStencilBufferClearValueHandler() {

    }

    void SetStencilBufferClearValueHandler::Run() {
        RenderCommandHandler::Run();
        glClearStencil(clearValue);
    }

    void SetStencilBufferClearValueHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilBufferClearValueHandler>::Release(this);
    }
} // DivineBrush