//
// Created by onelei on 2024/5/31.
//

#ifndef ENGINE_HORIZONTALLAYOUT_H
#define ENGINE_HORIZONTALLAYOUT_H

#include "imgui.h"
#include <vector>
#include <functional>
#include <imgui_internal.h>

namespace DivineBrush::Editor {
    class HorizontalLayout {
    public:
        static void Begin(int numColumns) {
            ImGui::Columns(numColumns, "mycolumns");
            currentColumn = 0;
            columnWidths.resize(numColumns, 0.0f);
            currentXs.resize(numColumns, 0.0f);
            elements.resize(numColumns);
        }

        static void NextColumn() {
            if (currentColumn < numColumns - 1) {
                currentColumn++;
                ImGui::NextColumn();
            }
        }

        static void Button(const char* label) {
            elements[currentColumn].push_back([label]() { ImGui::Button(label);ImGui::SameLine(); });
        }

        static void Text(const char* text) {
            elements[currentColumn].push_back([text]() { ImGui::Text("%s", text);ImGui::SameLine(); });
        }

        static void Space(float space) {
            elements[currentColumn].push_back([space]() { ImGui::Dummy(ImVec2(space, 0)); ImGui::SameLine();});
        }

        static void End() {
            for (int col = 0; col < numColumns; ++col) {
                columnWidths[col] = ImGui::GetColumnWidth();
                currentXs[col] = ImGui::GetCursorPosX();
            }

            for (int col = 0; col < numColumns; ++col) {
                float totalWidth = 0.0f;
                std::vector<float> elementWidths;

                // 计算所有元素的总宽度
                for (const auto& element : elements[col]) {
                    ImGui::PushID(&element);
                    ImVec2 size = ImGui::CalcItemSize(ImVec2(0, 0), 0, 0);
                    ImGui::PopID();
                    elementWidths.push_back(size.x);
                    totalWidth += size.x;
                }

                // 计算对齐的X位置
                float startX = currentXs[col];
                if (totalWidth < columnWidths[col]) {
                    startX += (columnWidths[col] - totalWidth) / 2.0f; // 居中对齐
                }

                // 设置元素的位置并绘制
                ImGui::SetCursorPosX(startX);
                for (size_t i = 0; i < elements[col].size(); ++i) {
                    elements[col][i]();
                    if (i < elements[col].size() - 1) {
                        ImGui::SameLine();
                    }
                }

                if (col < numColumns - 1) {
                    ImGui::NextColumn();
                }
            }

            ImGui::Columns(1);

            // 清理数据以便下一次使用
            columnWidths.clear();
            currentXs.clear();
            elements.clear();
        }

    private:
        static int numColumns;
        static int currentColumn;
        static std::vector<float> columnWidths;
        static std::vector<float> currentXs;
        static std::vector<std::vector<std::function<void()>>> elements;
    };

// 初始化静态成员变量
    int HorizontalLayout::numColumns = 1;
    int HorizontalLayout::currentColumn = 0;
    std::vector<float> HorizontalLayout::columnWidths;
    std::vector<float> HorizontalLayout::currentXs;
    std::vector<std::vector<std::function<void()>>> HorizontalLayout::elements;
}

#endif //ENGINE_HORIZONTALLAYOUT_H
