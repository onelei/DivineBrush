//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETBLENDFUNCHANDLER_H
#define ENGINE_SETBLENDFUNCHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class SetBlendFuncHandler : public RenderCommandHandler {
    public:
        SetBlendFuncHandler() {
            renderCommand = RenderCommand::SetBlendFunc;
        }

        ~SetBlendFuncHandler() = default;

        unsigned int sourceFactor = 0;
        unsigned int destinationFactor = 0;
    };
} // DivineBrush

#endif //ENGINE_SETBLENDFUNCHANDLER_H
