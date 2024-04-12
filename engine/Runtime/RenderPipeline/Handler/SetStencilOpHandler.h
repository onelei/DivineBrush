//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETSTENCILOPHANDLER_H
#define ENGINE_SETSTENCILOPHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class SetStencilOpHandler : public RenderCommandHandler {
    public:
        SetStencilOpHandler() {
            renderCommand = RenderCommand::SetStencilOp;
        }

        ~SetStencilOpHandler() = default;

        unsigned int fail = 0;
        unsigned int zTestFail = 0;
        unsigned int zTestPass = 0;
    };

} // DivineBrush

#endif //ENGINE_SETSTENCILOPHANDLER_H
