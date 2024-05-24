//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETUNIFORMINTHANDLER_H
#define ENGINE_SETUNIFORMINTHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class SetUniformIntHandler : public RenderCommandHandler {
    public:
        SetUniformIntHandler();

        ~SetUniformIntHandler();

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        int value = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_SETUNIFORMINTHANDLER_H
