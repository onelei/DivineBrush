//
// Created by onelei on 2024/5/31.
//

#ifndef ENGINE_VERTICALLAYOUT_H
#define ENGINE_VERTICALLAYOUT_H

#include "imgui.h"
#include "imgui_internal.h"

namespace DivineBrush {

    class VerticalLayout {
    public:
        static void Begin(float width = 0.0f, float height = 0.0f) {
            if (width <= 0.0f || height <= 0.0f) {
                ImVec2 windowSize = ImGui::GetWindowSize();
                if (width <= 0.0f) width = windowSize.x;
                if (height <= 0.0f) height = windowSize.y;
            }

            m_width = width;
            m_height = height;
            m_x = 0.0f;
            m_y = 0.0f;
            m_occupiedHeight = 0.0f;
            m_spacingCount = 0;
            ImGui::BeginChild("VerticalLayout", ImVec2(width, height), false, ImGuiWindowFlags_NoScrollbar);
            m_x = ImGui::GetCursorPosX();
            m_y = ImGui::GetCursorPosY();
        }

        static void End() {
            ImGui::EndChild();
        }

        static void Button(const char *label) {
            if (m_y != ImGui::GetCursorPosY()) {
                ImGui::SameLine();
            }
            if (ImGui::Button(label)) {
                // Do something when the button is clicked
            }
            m_occupiedHeight += ImGui::CalcTextSize(label).y + ImGui::GetStyle().FramePadding.y * 2 +
                                ImGui::GetStyle().ItemSpacing.y;
            m_y = ImGui::GetCursorPosY();
        }

        static void Space(float height = 0.0f) {
            if (height <= 0.0f) {
                height = (m_height - m_occupiedHeight) / (m_spacingCount + 1); // Distribute remaining space
                m_spacingCount++;
            }
            ImGui::SetCursorPosY(m_y + height);
            m_y = ImGui::GetCursorPosY();
            m_occupiedHeight += height;
        }

    private:
        static float m_width;
        static float m_height;
        static float m_x;
        static float m_y;
        static float m_occupiedHeight;
        static int m_spacingCount;
    };

    float VerticalLayout::m_width = 0.0f;
    float VerticalLayout::m_height = 0.0f;
    float VerticalLayout::m_x = 0.0f;
    float VerticalLayout::m_y = 0.0f;
    float VerticalLayout::m_occupiedHeight = 0.0f;
    int VerticalLayout::m_spacingCount = 0;

} // DivineBrush

#endif //ENGINE_VERTICALLAYOUT_H
