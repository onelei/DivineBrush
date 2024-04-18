//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_ACTIVEANDBINDTEXTUREHANDLER_H
#define ENGINE_ACTIVEANDBINDTEXTUREHANDLER_H

#include "../RenderCommand.h"
#include "RenderCommandHandler.h"

namespace DivineBrush {

    class ActiveAndBindTextureHandler : public RenderCommandHandler {
    public:
        ActiveAndBindTextureHandler() {
            renderCommand = RenderCommand::ActiveAndBindTexture;
        }

        ~ActiveAndBindTextureHandler() override = default;

        unsigned int textureUnit = 0;
        unsigned int textureHandle = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_ACTIVEANDBINDTEXTUREHANDLER_H
