//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_ENDFRAMEHANDLER_H
#define ENGINE_ENDFRAMEHANDLER_H

#include "AsyncRenderCommandHandler.h"

namespace DivineBrush {

    class EndFrameHandler : public AsyncRenderCommandHandler {
    public:
        EndFrameHandler() {
            renderCommand = RenderCommand::EndFrame;
        }

        ~EndFrameHandler() = default;

        void Run() override;
    };

} // DivineBrush

#endif //ENGINE_ENDFRAMEHANDLER_H
