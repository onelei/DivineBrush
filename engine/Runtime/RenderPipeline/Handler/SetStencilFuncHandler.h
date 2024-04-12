//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETSTENCILFUNCHANDLER_H
#define ENGINE_SETSTENCILFUNCHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class SetStencilFuncHandler : public RenderCommandHandler {
    public:
        SetStencilFuncHandler() {
            renderCommand = RenderCommand::SetStencilFunc;
        }

        ~SetStencilFuncHandler() = default;

        unsigned int func = 0;
        int ref = 0;
        unsigned int mask = 0;
    };

} // DivineBrush

#endif //ENGINE_SETSTENCILFUNCHANDLER_H
