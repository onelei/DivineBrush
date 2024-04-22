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


        virtual void Run();

        virtual void Clear();

        bool GetIsWait(){
            return isWait;
        };

        RenderCommand GetRenderCommand(){
            return renderCommand;
        }

    protected:
        RenderCommand renderCommand = DivineBrush::RenderCommand::None;

        bool isWait = false;
        bool isFinish = false;
    };
} // DivineBrush

#endif //ENGINE_RENDERCOMMANDHANDLER_H
