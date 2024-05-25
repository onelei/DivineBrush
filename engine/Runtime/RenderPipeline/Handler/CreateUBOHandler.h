//
// Created by onelei on 2024/5/24.
//

#ifndef ENGINE_CREATEUBOHANDLER_H
#define ENGINE_CREATEUBOHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class CreateUBOHandler : public RenderCommandHandler {
    public:
        CreateUBOHandler();

        ~CreateUBOHandler();

        unsigned int shaderProgramHandle = 0;
        unsigned int uboHandle = 0;
        char *name = nullptr;
        unsigned int size = 0;
        void *data = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_CREATEUBOHANDLER_H
