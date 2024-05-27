//
// Created by onelei on 2024/3/1.
//

#include "imgui.h"
#include "HierarchyWindow.h"
#include "../../Runtime/Component/GameObject.h"
#include "../Selection.h"

namespace DivineBrush::Editor {

    HierarchyWindow::HierarchyWindow() : EditorWindow(k_Hierarchy) {

    }

    HierarchyWindow::~HierarchyWindow() {
        EditorWindow::~EditorWindow();
    }

    void HierarchyWindow::OnPrepareGUI() {
        EditorWindow::OnPrepareGUI();
        auto topHeight = EditorWindow::GetScreenHeight() / 8;
        auto minWidth = 200;
        // 设置窗口的起点位置
        ImVec2 windowPos = ImVec2(0, topHeight);
        ImGui::SetNextWindowPos(windowPos);
        // 设置窗口的大小
        ImVec2 windowSize = ImVec2(minWidth, EditorWindow::GetScreenHeight() - topHeight * 2);
        ImGui::SetNextWindowSize(windowSize);
    }

    void HierarchyWindow::OnGUI() {
        auto base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
                          ImGuiTreeNodeFlags_SpanAvailWidth;
        auto root_node = GameObject::GetRootNode();
        DrawTreeNode(root_node, "Scene", base_flags);
    }

    void HierarchyWindow::DrawTreeNode(Node *node, const char *name, ImGuiTreeNodeFlags parentFlags) {
        auto flags = parentFlags;
        auto selectedNode = Selection::GetSelectedNode();
        if (selectedNode == node) {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        auto children = node->GetChildren();
        if (!children.empty()) {
            if (ImGui::TreeNodeEx(name, flags)) {
                if (ImGui::IsItemClicked()) {
                    Selection::SetSelectedNode(node);
                }
                for (auto *child: children) {
                    auto gameObject = dynamic_cast<GameObject *>(child);
                    DrawTreeNode(child, gameObject->GetName(), parentFlags);
                }
                ImGui::TreePop();
            }
        } else {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            ImGui::TreeNodeEx(name, flags);
            if (ImGui::IsItemClicked()) {
                Selection::SetSelectedNode(node);
            }
        }
    }


} // DivineBrush