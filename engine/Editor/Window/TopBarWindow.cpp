//
// Created by onelei on 2024/5/31.
//

#include <GL/glew.h>
#include "TopBarWindow.h"
#include "Layouts/GUILayout.h"
#include "../../Runtime/UI/Texture2D.h"
#include "../../depends/stacklayout/imgui_stacklayout.h"

namespace DivineBrush::Editor {
    TopBarWindow::TopBarWindow() : EditorWindow(k_TopBar) {
        dragButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_ViewToolMove On@2x.png");
        moveButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_MoveTool@2x.png");
        rotateButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_RotateTool@2x.png");
        scaleButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_ScaleTool@2x.png");
        rectButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_RectTool@2x.png");

        playButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/PlayButton On@2x.png");
        pauseButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/PauseButton On@2x.png");
        nextButtonTextureId = (void *) (intptr_t)Texture2D::LoadGLTextureId("../Resources/d_StepButton On@2x.png");
    }

    TopBarWindow::~TopBarWindow() {
        EditorWindow::~EditorWindow();
    }

    void TopBarWindow::OnGUI() {

        // Draw menu bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Assets")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("GameObject")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Component")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Draw toolbar
        ImGui::Separator();

        // 创建三列
        ImGui::Columns(3, "columns");
        float availableHeight = 10;
        // 第一列：左对齐
        float buttonWidth = 10.0f; // 按钮宽度
        ImGui::ImageButton( dragButtonTextureId , ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( moveButtonTextureId , ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( rotateButtonTextureId , ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( scaleButtonTextureId , ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( rectButtonTextureId , ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        // 移动到下一列
        ImGui::NextColumn();

        // 第二列：居中对齐
        float columnWidth = ImGui::GetColumnWidth();
        buttonWidth = 10.0f; // 按钮宽度
        float spacing = ImGui::GetStyle().ItemSpacing.x; // Spacing between buttons
        float totalButtonWidth = 3 * buttonWidth + 2 * spacing; // Total width of buttons and spacing
        float availableWidth = ImGui::GetContentRegionAvail().x; // Available width in the column
        // Calculate the remaining space to be divided on both sides
        float remainingSpace = availableWidth - totalButtonWidth;
        float halfSpace = remainingSpace / 2.0f;

        // Create a dummy item to push buttons to the center
        ImGui::Dummy(ImVec2(halfSpace, 0)); // Adjust dummy width to push buttons to the center
        ImGui::SameLine();

        ImGui::ImageButton( playButtonTextureId, ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( pauseButtonTextureId, ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        ImGui::ImageButton( nextButtonTextureId, ImVec2(buttonWidth, availableHeight));
        ImGui::SameLine();
        // 移动到下一列
        ImGui::NextColumn();

        // 第三列：右对齐
        //buttonWidth = 300.0f; // 按钮宽度
        //float rightPadding = (columnWidth - buttonWidth);

        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + rightPadding); // 设置X位置
        // Create a dummy item to push buttons to the right
        availableWidth = ImGui::GetContentRegionAvail().x;
        buttonWidth = 80.0f; // Width of each button
        spacing = ImGui::GetStyle().ItemSpacing.x; // Spacing between buttons
        totalButtonWidth = 3 * buttonWidth + 2 * spacing; // Total width of buttons and spacing
        ImGui::Dummy(ImVec2(availableWidth - totalButtonWidth, 0)); // Adjust dummy width to push buttons to the right

        // Account
        ImGui::SameLine();
        ImGui::PushItemWidth(buttonWidth);
        {
            const char *items[] = {"Account", "Account1"};
            static int item_current = 0;
            if (ImGui::Combo("##combo", &item_current, items, IM_ARRAYSIZE(items))) {

            }
            ImGui::PopItemWidth();
        }
        // Layers
        ImGui::SameLine();
        ImGui::PushItemWidth(buttonWidth);
        {
            const char *items[] = {"Layers", "Layers1"};
            static int item_current = 0;
            if (ImGui::Combo("##combo", &item_current, items, IM_ARRAYSIZE(items))) {

            }
            ImGui::PopItemWidth();
        }
        // Layout
        ImGui::SameLine();
        ImGui::PushItemWidth(buttonWidth);
        {
            const char *items[] = {"Layout", "Layout1"};
            static int item_current = 0;
            if (ImGui::Combo("##combo", &item_current, items, IM_ARRAYSIZE(items))) {

            }
            ImGui::PopItemWidth();
        }

        // 结束窗口
        ImGui::Columns(1);

        ImGui::Spacing();
        ImGui::Separator();
    }
}// DivineBrush::Editor