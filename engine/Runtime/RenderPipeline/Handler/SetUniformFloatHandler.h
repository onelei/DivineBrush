//
// Created by onelei on 2024/5/24.
//

#ifndef ENGINE_SETUNIFORMFLOATHANDLER_H
#define ENGINE_SETUNIFORMFLOATHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class SetUniformFloatHandler : public RenderCommandHandler {
    public:
        SetUniformFloatHandler();

        ~SetUniformFloatHandler();

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        float value = 0.0f;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_SETUNIFORMFLOATHANDLER_H
