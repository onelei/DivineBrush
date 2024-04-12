//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETSTATEENABLEHANDLER_H
#define ENGINE_SETSTATEENABLEHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class SetStateEnableHandler : public RenderCommandHandler {
    public:
        SetStateEnableHandler() {
            renderCommand = RenderCommand::SetStateEnable;
        }

        ~SetStateEnableHandler() = default;

        unsigned int state = 0;
        bool enable = false;
    };


} // DivineBrush

#endif //ENGINE_SETSTATEENABLEHANDLER_H
