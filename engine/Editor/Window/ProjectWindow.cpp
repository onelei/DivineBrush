//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "ProjectWindow.h"

namespace DivineBrush::Editor {

    ProjectWindow::ProjectWindow() : EditorWindow(k_Project) {

    }

    ProjectWindow::~ProjectWindow() {
        EditorWindow::~EditorWindow();
    }

    void ProjectWindow::OnGUI() {

        static float f = 0.0f;
        static int counter = 0;

        ImGui::Text("ProjectWindow");

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float *) &this->clear_color); // Edit 3 floats representing a color

        if (ImGui::Button(
                "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

    }

} // DivineBrush