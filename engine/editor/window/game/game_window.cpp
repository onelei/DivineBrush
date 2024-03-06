//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "game_window.h"
#include "../../../runtime/ui/image/image.h"

namespace DivineBrush::Editor {
    GLuint textureID;
    GameWindow::GameWindow() : EditorWindow(k_Game) {

    }

    GameWindow::~GameWindow() {
        EditorWindow::~EditorWindow();
    }

    void GameWindow::OnGUI() {
        {
            static float f = 0.0f;
            static int counter = 0;

            if(textureID <= 0)
            {
                textureID =
                    DivineBrush::UI::Image::LoadImageToTextureID("../samples/image/sample.png");
            }
            ImGui::Image((void*)(intptr_t)textureID, ImVec2(512, 512));

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
