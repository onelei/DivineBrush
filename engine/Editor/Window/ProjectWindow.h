//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_PROJECTWINDOW_H
#define ENGINE_PROJECTWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    class ProjectWindow : public EditorWindow {
    public:
        ProjectWindow();

        ~ProjectWindow();

        void OnGUI() override;

    private:
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
} // DivineBrush

#endif //ENGINE_PROJECTWINDOW_H
