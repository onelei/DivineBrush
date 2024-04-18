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

        ~SetBlendFuncHandler() override = default;

        unsigned int sFactor = 0;
        unsigned int dFactor = 0;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_SETBLENDFUNCHANDLER_H
