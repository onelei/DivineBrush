//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_DELETETEXTURESHANDLER_H
#define ENGINE_DELETETEXTURESHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {
    class DeleteTexturesHandler : public RenderCommandHandler {
    public:
        DeleteTexturesHandler() {
            renderCommand = RenderCommand::DeleteTextures;
        }

        ~DeleteTexturesHandler() override = default;

        unsigned int *textureHandleArray = nullptr;
        int textureCount = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_DELETETEXTURESHANDLER_H
