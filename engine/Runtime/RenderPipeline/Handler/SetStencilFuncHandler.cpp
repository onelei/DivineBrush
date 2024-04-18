//
// Created by onelei on 2024/4/11.
//

#include "SetStencilFuncHandler.h"
#include "GL/glew.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetStencilFuncHandler::Run() {
        RenderCommandHandler::Run();
        glStencilFunc(func, ref, mask);
    }

    void SetStencilFuncHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilFuncHandler>::Release(this);
    }
} // DivineBrush