//
// Created by onelei on 2024/5/31.
//

#ifndef ENGINE_GUILAYOUT_H
#define ENGINE_GUILAYOUT_H

#include "imgui.h"

namespace DivineBrush::Editor {
    class GUILayout {
    public:
        static void BeginHorizontal() {
            ImGui::BeginGroup();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        }

        static void EndHorizontal() {
            ImGui::PopStyleVar();
            ImGui::EndGroup();
        }

        static void FlexibleSpace() {
            ImGui::Dummy(ImVec2(0, 0)); // 创建一个不可见的占位符
            ImGui::SameLine(0.0f, -1.0f); // 保持在同一行
        }
    };
}

#endif //ENGINE_GUILAYOUT_H
