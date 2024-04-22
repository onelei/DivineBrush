//
// Created by onelei on 2024/3/1.
//

#ifndef ENGINE_HIERARCHYWINDOW_H
#define ENGINE_HIERARCHYWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"
#include "../../depends/node/Node.h"

namespace DivineBrush::Editor {
    class EditorWindow;
}

namespace DivineBrush::Editor {

    class HierarchyWindow : public EditorWindow {
    public:
        HierarchyWindow();

        ~HierarchyWindow();

        void OnGUI() override;

        void DrawTreeNode(Node *node, const char *name, ImGuiTreeNodeFlags flags);
    };
} // DivineBrush

#endif //ENGINE_HIERARCHYWINDOW_H
