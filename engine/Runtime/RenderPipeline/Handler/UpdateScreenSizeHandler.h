//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_UPDATESCREENSIZEHANDLER_H
#define ENGINE_UPDATESCREENSIZEHANDLER_H

#include "RenderCommandHandler.h"
#include "GLFW/glfw3.h"

namespace DivineBrush {
    class UpdateScreenSizeHandler : public RenderCommandHandler {
    public:
        UpdateScreenSizeHandler();

        ~UpdateScreenSizeHandler();

        GLFWwindow *window = nullptr;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_UPDATESCREENSIZEHANDLER_H
