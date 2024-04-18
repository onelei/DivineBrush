//
// Created by onelei on 2024/4/11.
//

#include "SetClearFlagAndClearColorBufferHandler.h"
#include "GL/glew.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetClearFlagAndClearColorBufferHandler::Run() {
        RenderCommandHandler::Run();
        glClear(clearFlag);
        glClearColor(clearColorR, clearColorG, clearColorB, clearColorA);
    }

    void SetClearFlagAndClearColorBufferHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetClearFlagAndClearColorBufferHandler>::Release(this);
    }
} // DivineBrush