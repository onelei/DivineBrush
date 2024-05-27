//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_INSPECTORWINDOW_H
#define ENGINE_INSPECTORWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    class EditorWindow;
}

namespace DivineBrush::Editor {
    class InspectorWindow : public EditorWindow {
    public:
        InspectorWindow();

        ~InspectorWindow();

        void OnPrepareGUI() override;

        void OnGUI() override;

    private:
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
} // DivineBrush

#endif //ENGINE_INSPECTORWINDOW_H
