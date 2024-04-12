//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_COMPILESHADERHANDLER_H
#define ENGINE_COMPILESHADERHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"
#include <string>

namespace DivineBrush {

    class CompileShaderHandler : public RenderCommandHandler {
    public:
        CompileShaderHandler(){
            renderCommand = RenderCommand::CompileShader;
        }

        ~CompileShaderHandler() {
            //free(vertexShaderSource);
            //free(fragmentShaderSource);
        }

        std::string vertexShaderSource;
        std::string fragmentShaderSource;
        unsigned int shaderProgramHandle = 0;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_COMPILESHADERHANDLER_H
