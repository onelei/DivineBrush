//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETCLEARFLAGANDCLEARCOLORBUFFERHANDLER_H
#define ENGINE_SETCLEARFLAGANDCLEARCOLORBUFFERHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class SetClearFlagAndClearColorBufferHandler : public RenderCommandHandler {
    public:
        SetClearFlagAndClearColorBufferHandler() {
            renderCommand = RenderCommand::SetClearFlagAndClearColorBuffer;
        }

        ~SetClearFlagAndClearColorBufferHandler() override = default;

        unsigned int clearFlag = 0;
        float clearColorR = 0.0f;
        float clearColorG = 0.0f;
        float clearColorB = 0.0f;
        float clearColorA = 0.0f;

        void Run() override;

        void Clear() override;
    };


} // DivineBrush

#endif //ENGINE_SETCLEARFLAGANDCLEARCOLORBUFFERHANDLER_H
