//
// Created by onelei on 2024/4/10.
//

#include "AsyncRenderCommandHandler.h"

namespace DivineBrush {
    void AsyncRenderCommandHandler::Wait() {
        while (!isFinish) {

        }
    }

    void AsyncRenderCommandHandler::Run() {
        RenderCommandHandler::Run();
    }

    void AsyncRenderCommandHandler::Clear() {
        RenderCommandHandler::Clear();
        isWait = true;
        isFinish = false;
    }
} // DivineBrush