//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "ConsoleWindow.h"

namespace DivineBrush::Editor {

    ConsoleWindow::ConsoleWindow() : EditorWindow(k_Console) {

    }

    ConsoleWindow::~ConsoleWindow() {
        EditorWindow::~EditorWindow();
    }

    void ConsoleWindow::OnPrepareGUI() {
        EditorWindow::OnPrepareGUI();
        auto topHeight = EditorWindow::GetScreenHeight() / 8;
        auto minWidth = 200;
        auto minHeight = topHeight;
        // 设置窗口的起点位置
        ImVec2 windowPos = ImVec2(0, EditorWindow::GetScreenHeight() - topHeight);
        ImGui::SetNextWindowPos(windowPos);
        // 设置窗口的大小
        ImVec2 windowSize = ImVec2(EditorWindow::GetScreenWidth() - minWidth, minHeight);
        ImGui::SetNextWindowSize(windowSize);
    }

    void ConsoleWindow::OnGUI() {
        {
            static float f = 0.0f;
            static int counter = 0;


            ImGui::Text(
                    "Scene");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &this->clear_color); // Edit 3 floats representing a color

            if (ImGui::Button(
                    "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
        }
    }


} // DivineBrush