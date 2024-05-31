//
// Created by onelei on 2024/5/31.
//

#ifndef ENGINE_TOPBARWINDOW_H
#define ENGINE_TOPBARWINDOW_H

#include "EditorWindow.h"
#include "imgui.h"

namespace DivineBrush::Editor {
    class TopBarWindow : public EditorWindow {
    public:
        TopBarWindow();

        ~TopBarWindow() override;

        void OnGUI() override;
    };
}// DivineBrush::Editor

#endif //ENGINE_TOPBARWINDOW_H
