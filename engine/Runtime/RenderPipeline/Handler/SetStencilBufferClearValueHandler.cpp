//
// Created by onelei on 2024/4/11.
//

#include "SetStencilBufferClearValueHandler.h"
#include "GL/glew.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetStencilBufferClearValueHandler::Run() {
        RenderCommandHandler::Run();
        glClearStencil(clearValue);
    }

    void SetStencilBufferClearValueHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilBufferClearValueHandler>::Release(this);
    }
} // DivineBrush