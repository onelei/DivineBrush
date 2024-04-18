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

        ~SetStencilOpHandler() override = default;

        unsigned int fail = 0;
        unsigned int zFail = 0;
        unsigned int zPass = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_SETSTENCILOPHANDLER_H
