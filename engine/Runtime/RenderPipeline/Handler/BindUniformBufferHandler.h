//
// Created by onelei on 2024/5/24.
//

#ifndef ENGINE_BINDUNIFORMBUFFERHANDLER_H
#define ENGINE_BINDUNIFORMBUFFERHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class BindUniformBufferHandler : public RenderCommandHandler {
    public:
        BindUniformBufferHandler();

        ~BindUniformBufferHandler();

        unsigned int shaderProgramHandle = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_BINDUNIFORMBUFFERHANDLER_H
