//
// Created by onelei on 2024/5/28.
//

#include "BaseLayout.h"

namespace DivineBrush {

    BaseLayout::~BaseLayout() {

    }

    void BaseLayout::GUI(ImGuiIO *io) {
        OnBeginDockSpace();
        if (!isInitLayout) {
            OnInitLayout();
            isInitLayout = true;
        }
        OnGUI(io);
    }

    void BaseLayout::OnBeginDockSpace() {

    }

    void BaseLayout::OnInitLayout() {

    }

    void BaseLayout::OnGUI(ImGuiIO *io) {

    }

} // DivineBrush