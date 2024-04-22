//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_BINDVAOANDDRAWELEMENTSHANDLER_H
#define ENGINE_BINDVAOANDDRAWELEMENTSHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class BindVAOAndDrawElementsHandler : public RenderCommandHandler {
    public:
        BindVAOAndDrawElementsHandler();

        ~BindVAOAndDrawElementsHandler();

        unsigned int vaoHandle = 0;
        unsigned int vertexIndexCount = 0;

        void Run() override;

        void Clear() override;
    };
} // DivineBrush

#endif //ENGINE_BINDVAOANDDRAWELEMENTSHANDLER_H
