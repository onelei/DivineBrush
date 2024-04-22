//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_USESHADERPROGRAMHANDLER_H
#define ENGINE_USESHADERPROGRAMHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class UseShaderProgramHandler : public RenderCommandHandler {
    public:
        UseShaderProgramHandler();

        ~UseShaderProgramHandler();

        unsigned int shaderProgramHandle = 0;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_USESHADERPROGRAMHANDLER_H
