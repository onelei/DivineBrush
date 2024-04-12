//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_ASYNCRENDERCOMMANDHANDLER_H
#define ENGINE_ASYNCRENDERCOMMANDHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {

    class AsyncRenderCommandHandler : public RenderCommandHandler {
    public:
        AsyncRenderCommandHandler() {
            renderCommand = RenderCommand::None;
            //isNeedReturnResult = true;
        }

        ~AsyncRenderCommandHandler() = default;

        virtual void Wait();

        void Run() override;
    };


} // DivineBrush

#endif //ENGINE_ASYNCRENDERCOMMANDHANDLER_H
