//
// Created by onelei on 2024/4/10.
//

#include <GL/glew.h>
#include "UpdateScreenSizeHandler.h"
#include "../../Screen/Screen.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void UpdateScreenSizeHandler::Run() {
        RenderCommandHandler::Run();
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        Screen::SetScreenSize(width, height);
    }

    void UpdateScreenSizeHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::UpdateScreenSizeHandler>::Release(this);
    }
} // DivineBrush