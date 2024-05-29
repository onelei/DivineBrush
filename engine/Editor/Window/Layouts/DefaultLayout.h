//
// Created by onelei on 2024/5/28.
//

#ifndef ENGINE_DEFAULTLAYOUT_H
#define ENGINE_DEFAULTLAYOUT_H

#include "BaseLayout.h"

namespace DivineBrush ::Editor {
    class DefaultLayout : public BaseLayout {
    protected:
        void OnBeginDockSpace() override;

        void OnInitLayout() override;

        void OnGUI(ImGuiIO *io) override;
    };

} // DivineBrush

#endif //ENGINE_DEFAULTLAYOUT_H
