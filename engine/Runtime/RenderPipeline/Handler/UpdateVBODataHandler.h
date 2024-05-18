//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_UPDATEVBODATAHANDLER_H
#define ENGINE_UPDATEVBODATAHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class UpdateVBODataHandler : public RenderCommandHandler {
    public:
        UpdateVBODataHandler();

        ~UpdateVBODataHandler();

        unsigned int vboHandle = 0;
        unsigned int vertexDataSize = 0;
        void *vertexData = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_UPDATEVBODATAHANDLER_H
