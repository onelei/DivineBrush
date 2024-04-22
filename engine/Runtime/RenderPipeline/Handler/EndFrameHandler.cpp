//
// Created by onelei on 2024/4/11.
//

#include <GLFW/glfw3.h>
#include "EndFrameHandler.h"
#include "../../../depends/template/ObjectPool.h"

namespace DivineBrush {
    EndFrameHandler::EndFrameHandler() {
        renderCommand = DivineBrush::RenderCommand::EndFrame;
    }

    EndFrameHandler::~EndFrameHandler() {

    }

    void EndFrameHandler::Run() {
        AsyncRenderCommandHandler::Run();
        glfwSwapBuffers(window);
        isFinish = true;
    }

    void EndFrameHandler::Clear() {
        AsyncRenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::EndFrameHandler>::Release(this);
    }
} // DivineBrush