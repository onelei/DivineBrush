//
// Created by onelei on 2024/5/17.
//

#ifndef ENGINE_UPDATEUBODATAHANDLER_H
#define ENGINE_UPDATEUBODATAHANDLER_H

#include <string>
#include "RenderCommandHandler.h"

namespace DivineBrush {

    class UpdateUBODataHandler : public RenderCommandHandler {
    public:
        UpdateUBODataHandler();

        ~UpdateUBODataHandler();

        std::string name;
        std::string memberName;
        void *data;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_UPDATEUBODATAHANDLER_H
