//
// Created by onelei on 2024/4/11.
//

#include "SetBlendFuncHandler.h"
#include "GL/glew.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetBlendFuncHandler::Run() {
        RenderCommandHandler::Run();
        glBlendFunc(sFactor, dFactor);
    }

    void SetBlendFuncHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetBlendFuncHandler>::Release(this);
    }
} // DivineBrush