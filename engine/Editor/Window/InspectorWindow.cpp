//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "InspectorWindow.h"
#include "../../Runtime/Component/GameObject.h"
#include "../Selection.h"

namespace DivineBrush::Editor {

    InspectorWindow::InspectorWindow() : EditorWindow(k_Inspector) {

    }

    InspectorWindow::~InspectorWindow() {
        EditorWindow::~EditorWindow();
    }

    void InspectorWindow::OnPrepareGUI() {
        EditorWindow::OnPrepareGUI();
        auto topHeight = EditorWindow::GetScreenHeight() / 8;
        auto minWidth = 200;
        // 设置窗口的起点位置
        ImVec2 windowPos = ImVec2(EditorWindow::GetScreenWidth() - minWidth, topHeight);
        ImGui::SetNextWindowPos(windowPos);
        // 设置窗口的大小
        ImVec2 windowSize = ImVec2(minWidth, EditorWindow::GetScreenHeight() - topHeight * 2);
        ImGui::SetNextWindowSize(windowSize);
    }

    void InspectorWindow::OnGUI() {
        auto selectedNode = Selection::GetSelectedNode();
        if (selectedNode != nullptr) {
            auto gameObject = dynamic_cast<GameObject *>(selectedNode);
            if (gameObject != nullptr) {
                //Active
                bool isActive = gameObject->IsActive();
                if (ImGui::Checkbox("Active", &isActive)) {
                    gameObject->SetActive(isActive);
                }
                //Layer
                int layer = gameObject->GetLayer();
                if (ImGui::InputInt("Layer", &layer)) {
                    gameObject->SetLayer(layer);
                }
                //Transform
                auto transform = gameObject->GetComponent<Transform>();

                auto position = transform->GetPosition();
                auto rotation = transform->GetRotation();
                auto scale = transform->GetScale();
                if (ImGui::TreeNode("Transform")) {
                    if (ImGui::InputFloat3("Position", (float *) &position)) {
                        transform->SetPosition(position);
                    }
                    if (ImGui::InputFloat3("Rotation", (float *) &rotation)) {
                        transform->SetRotation(rotation);
                    }
                    if (ImGui::InputFloat3("Scale", (float *) &scale)) {
                        transform->SetScale(scale);
                    }
                    ImGui::TreePop();
                }
            }
        }
    }


} // DivineBrush