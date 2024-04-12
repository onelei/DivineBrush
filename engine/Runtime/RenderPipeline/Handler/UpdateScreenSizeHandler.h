//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_UPDATESCREENSIZEHANDLER_H
#define ENGINE_UPDATESCREENSIZEHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {


    class UpdateScreenSizeHandler : public RenderCommandHandler {
    public:
        UpdateScreenSizeHandler() {
            renderCommand = RenderCommand::UpdateScreenSize;
        }

        ~UpdateScreenSizeHandler() = default;

        void Run() override;
    };
} // DivineBrush

#endif //ENGINE_UPDATESCREENSIZEHANDLER_H
