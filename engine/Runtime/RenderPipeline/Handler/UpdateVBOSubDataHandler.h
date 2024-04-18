//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_UPDATEVBOSUBDATAHANDLER_H
#define ENGINE_UPDATEVBOSUBDATAHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class UpdateVBOSubDataHandler : public RenderCommandHandler {
    public:
        UpdateVBOSubDataHandler() {
            renderCommand = RenderCommand::UpdateVBOSubData;
        }

        ~UpdateVBOSubDataHandler() override = default;

        unsigned int vboHandle = 0;
        unsigned int vertexDataSize = 0;
        void *vertexData = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_UPDATEVBOSUBDATAHANDLER_H
