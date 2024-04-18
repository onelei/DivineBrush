//
// Created by onelei on 2024/4/11.
//

#include "SetStencilOpHandler.h"
#include "GL/glew.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetStencilOpHandler::Run() {
        RenderCommandHandler::Run();
        glStencilOp(fail, zFail, zPass);
    }

    void SetStencilOpHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStencilOpHandler>::Release(this);
    }
} // DivineBrush