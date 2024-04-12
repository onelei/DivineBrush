//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETUNIFORM1IHANDLER_H
#define ENGINE_SETUNIFORM1IHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class SetUniform1iHandler : public RenderCommandHandler {
    public:
        SetUniform1iHandler() {
            renderCommand = RenderCommand::SetUniform1i;
        }

        ~SetUniform1iHandler() {
            free(uniformName);
        }

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        int value = 0;
    };

} // DivineBrush

#endif //ENGINE_SETUNIFORM1IHANDLER_H
