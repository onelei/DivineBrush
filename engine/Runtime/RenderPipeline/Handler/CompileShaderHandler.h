//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_COMPILESHADERHANDLER_H
#define ENGINE_COMPILESHADERHANDLER_H

#include "cstdlib"
#include <string>
#include "RenderCommandHandler.h"

namespace DivineBrush {

    class CompileShaderHandler : public RenderCommandHandler {
    public:
        CompileShaderHandler();

        ~CompileShaderHandler();

        char *vertexShaderSource{};
        char *fragmentShaderSource{};
        unsigned int shaderProgramHandle = 0;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_COMPILESHADERHANDLER_H
