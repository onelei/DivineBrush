//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_USESHADERPROGRAMHANDLER_H
#define ENGINE_USESHADERPROGRAMHANDLER_H

#include "../RenderCommand.h"
#include "RenderCommandHandler.h"

namespace DivineBrush {

    class UseShaderProgramHandler : public RenderCommandHandler {
    public:
        UseShaderProgramHandler() {
            renderCommand = RenderCommand::UseShaderProgram;
        }

        ~UseShaderProgramHandler() = default;

        unsigned int shaderProgramHandle = 0;

        void Run() override;
    };


} // DivineBrush

#endif //ENGINE_USESHADERPROGRAMHANDLER_H
