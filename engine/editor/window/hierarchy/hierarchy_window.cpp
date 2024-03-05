//
// Created by onelei on 2024/3/1.
//

#include "imgui.h"
#include "hierarchy_window.h"

namespace DivineBrush::Editor {

    HierarchyWindow::HierarchyWindow() : EditorWindow(k_Hierarchy) {

    }

    HierarchyWindow::~HierarchyWindow() {
        EditorWindow::~EditorWindow();
    }

    void HierarchyWindow::OnGUI() {
        {
            if (ImGui::TreeNode("Tree Nodes")) {
                if (ImGui::TreeNode("Basic trees")) {
                    for (int i = 0; i < 5; i++) {
                        // Use SetNextItemOpen() so set the default state of a node to be open. We could
                        // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
                        if (i == 0)
                            ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                        if (ImGui::TreeNode((void *) (intptr_t) i, "Child %d", i)) {
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }
    }

} // DivineBrush