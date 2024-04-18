//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_ENDFRAMEHANDLER_H
#define ENGINE_ENDFRAMEHANDLER_H

#include "AsyncRenderCommandHandler.h"
#include "imgui_impl_glfw.h"

namespace DivineBrush {

    class EndFrameHandler : public AsyncRenderCommandHandler {
    public:
        EndFrameHandler() {
            renderCommand = RenderCommand::EndFrame;
        }

        ~EndFrameHandler() override = default;
        GLFWwindow* window = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_ENDFRAMEHANDLER_H
