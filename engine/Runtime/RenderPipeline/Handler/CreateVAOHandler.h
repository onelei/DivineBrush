//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_CREATEVAOHANDLER_H
#define ENGINE_CREATEVAOHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class CreateVAOHandler : public RenderCommandHandler {
    public:
        CreateVAOHandler();

        ~CreateVAOHandler();

        unsigned int shaderProgramHandle = 0;
        unsigned int vaoHandle = 0;
        unsigned int vboHandle = 0;
        unsigned int vertexDataSize = 0;
        void *vertexData = nullptr;
        unsigned int vertexIndexDataSize = 0;
        void *vertexIndexData = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_CREATEVAOHANDLER_H
