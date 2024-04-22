//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "SetStateEnableHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetStateEnableHandler::SetStateEnableHandler() {
        renderCommand = DivineBrush::RenderCommand::SetStateEnable;
    }

    SetStateEnableHandler::~SetStateEnableHandler() {

    }

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