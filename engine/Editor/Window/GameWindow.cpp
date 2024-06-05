//
// Created by onelei on 2024/3/5.
//

#include <GL/glew.h>
#include <GL/gl.h>
#include "imgui.h"
#include "GameWindow.h"
#include "../../runtime/Screen/Screen.h"
#include "../../runtime/RenderPipeline/RenderPipeline.h"

namespace DivineBrush::Editor {
    GLuint textureID;

    GameWindow::GameWindow() : EditorWindow(k_Game) {

    }

    GameWindow::~GameWindow() {
        EditorWindow::~EditorWindow();
    }

    void GameWindow::OnGUI() {
        auto windowsPos = ImGui::GetWindowPos();
        auto windowsSize = ImGui::GetWindowSize();
        Screen::SetXY(windowsPos.x, windowsPos.y);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Game")) {
                if (ImGui::MenuItem("Game", "Ctrl+N")) {}
                if (ImGui::MenuItem("Simulator", "Ctrl+O")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Display0")) {
                for (int i = 0; i < 8; ++i) {
                    if (ImGui::MenuItem("Display%d"+(i+1), "Ctrl+N"+i)) {}
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
        //使用FBO的纹理在ImGui中渲染：现在，你可以使用FBO的纹理作为源，通过ImGui渲染图像。
        textureID = RenderPipeline::GetColorTextureId();
        // ImGui绘制Image，使用FBO Attach Texture id
        // 第一个参数：生成的纹理的id
        // 第2个参数：Image的大小
        // 第3，4个参数：UV的起点坐标和终点坐标，UV是被规范化到（0，1）之间的坐标
        // 第5个参数：图片的色调
        // 第6个参数：图片边框的颜色
        //ImGui::Image((void*)(intptr_t)textureID, ImVec2(480,320), ImVec2(0.0, 1.0), ImVec2(1.0, 0.0), ImVec4(1, 1, 1, 1), ImVec4(0, 1, 0, 1));
        ImGui::Image((void *) (intptr_t) textureID, windowsSize);

    }

} // DivineBrush
