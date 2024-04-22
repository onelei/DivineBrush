//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETSTENCILBUFFERCLEARVALUEHANDLER_H
#define ENGINE_SETSTENCILBUFFERCLEARVALUEHANDLER_H

#include "RenderCommandHandler.h"

namespace DivineBrush {
    class SetStencilBufferClearValueHandler : public RenderCommandHandler {
    public:
        SetStencilBufferClearValueHandler();

        ~SetStencilBufferClearValueHandler();

        int clearValue = 0;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_SETSTENCILBUFFERCLEARVALUEHANDLER_H
