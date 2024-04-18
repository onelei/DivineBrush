//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_RENDERCOMMANDHANDLER_H
#define ENGINE_RENDERCOMMANDHANDLER_H

#include "../RenderCommand.h"

namespace DivineBrush {

    class RenderCommandHandler {
    public:
        RenderCommandHandler();

        virtual ~RenderCommandHandler();

        RenderCommand renderCommand = RenderCommand::None;

        bool isWait = false;
        bool isFinish = false;
        virtual void Run();

        virtual void Clear();
    };
} // DivineBrush

#endif //ENGINE_RENDERCOMMANDHANDLER_H
