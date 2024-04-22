//
// Created by onelei on 2024/4/11.
//

#include "GL/glew.h"
#include "SetClearFlagAndClearColorBufferHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    SetClearFlagAndClearColorBufferHandler::SetClearFlagAndClearColorBufferHandler() {
        renderCommand = DivineBrush::RenderCommand::SetClearFlagAndClearColorBuffer;
    }

    SetClearFlagAndClearColorBufferHandler::~SetClearFlagAndClearColorBufferHandler() {

    }

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