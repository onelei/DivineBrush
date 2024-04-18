//
// Created by onelei on 2024/4/11.
//

#include "EndFrameHandler.h"
#include <GLFW/glfw3.h>
#include "../../template/ObjectPool.h"

namespace DivineBrush {
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