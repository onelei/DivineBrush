//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_UPDATETEXTURESUBIMAGE2DHANDLER_H
#define ENGINE_UPDATETEXTURESUBIMAGE2DHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class UpdateTextureSubImage2DHandler : public RenderCommandHandler {
    public:
        UpdateTextureSubImage2DHandler() {
            renderCommand = RenderCommand::UpdateTextureSubImage2D;
        }

        ~UpdateTextureSubImage2DHandler() override = default;

        unsigned int textureHandle = 0;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        unsigned int format = 0;
        unsigned int type = 0;
        unsigned char *data = nullptr;
        unsigned int dataSize = 0;

        void Run() override;
        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_UPDATETEXTURESUBIMAGE2DHANDLER_H
