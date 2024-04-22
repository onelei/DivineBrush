//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_CREATECOMPRESSEDTEXIMAGE2DHANDLER_H
#define ENGINE_CREATECOMPRESSEDTEXIMAGE2DHANDLER_H

#include <cstdlib>
#include "RenderCommandHandler.h"

namespace DivineBrush {

    class CreateCompressedTexImage2DHandler : public RenderCommandHandler {

    public:
        CreateCompressedTexImage2DHandler();

        ~CreateCompressedTexImage2DHandler();

        unsigned int textureHandle = 0;
        int width = 0;
        int height = 0;
        unsigned int textureFormat = 0;
        int compressSize = 0;
        unsigned char *data = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_CREATECOMPRESSEDTEXIMAGE2DHANDLER_H
