//
// Created by onelei on 2024/5/28.
//

#ifndef ENGINE_BASELAYOUT_H
#define ENGINE_BASELAYOUT_H

#include "unordered_map"
#include "string"
#include <imgui_internal.h>

namespace DivineBrush {

    class BaseLayout {
    public:
        virtual ~BaseLayout();

        void GUI(ImGuiIO *io);

    protected:
        virtual void OnBeginDockSpace();

        virtual void OnInitLayout();

        virtual void OnGUI(ImGuiIO *io);

        ImGuiIO *io;
        ImGuiID dockspaceId;
        bool isInitLayout = false;
    };

} // DivineBrush

#endif //ENGINE_BASELAYOUT_H
