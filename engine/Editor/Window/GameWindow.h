//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_GAMEWINDOW_H
#define ENGINE_GAMEWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    class GameWindow : public EditorWindow {
    public:
        GameWindow();

        ~GameWindow() override;

        void OnGUI() override;

    private:
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
} // DivineBrush

#endif //ENGINE_GAMEWINDOW_H
