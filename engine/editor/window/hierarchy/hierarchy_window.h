//
// Created by onelei on 2024/3/1.
//

#ifndef ENGINE_HIERARCHY_WINDOW_H
#define ENGINE_HIERARCHY_WINDOW_H

#include <imgui.h>
#include "../editor_window.h"

namespace DivineBrush::Editor {
    class EditorWindow;
}

namespace DivineBrush::Editor {

    class HierarchyWindow : public EditorWindow {
    public:
        HierarchyWindow();

        ~HierarchyWindow();

        void OnGUI() override;

    private:
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
} // DivineBrush

#endif //ENGINE_HIERARCHY_WINDOW_H
