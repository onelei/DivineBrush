//
// Created by onelei on 2024/4/11.
//

#include "SetStateEnableHandler.h"
#include <GL/glew.h>
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void SetStateEnableHandler::Run() {
        RenderCommandHandler::Run();
        if (enable) {
            glEnable(state);
        } else {
            glDisable(state);
        }
    }

    void SetStateEnableHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::SetStateEnableHandler>::Release(this);
    }
} // DivineBrush