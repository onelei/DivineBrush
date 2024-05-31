//
// Created by onelei on 2024/5/31.
//

#include <GL/glew.h>
#include "TopBarWindow.h"
#include "Layouts/HorizontalLayout.h"

namespace DivineBrush::Editor {
    TopBarWindow::TopBarWindow() : EditorWindow(k_TopBar) {

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

//        HorizontalLayout::Begin(0,20.0f);{
//            HorizontalLayout::Button("Left");
//            HorizontalLayout::Button("Left2");
//            HorizontalLayout::Button("Left3");
//            HorizontalLayout::Space();
//            HorizontalLayout::Button("Center");
//            HorizontalLayout::Button("Center2");
//            HorizontalLayout::Button("Center3");
//            HorizontalLayout::Space();
//            HorizontalLayout::Button("Right");
//            HorizontalLayout::Button("Right1");
//        }
//        HorizontalLayout::End();

        // 创建水平布局管理器
//        HorizontalLayout::Begin(3);
//
//        // 第一列：左对齐
//        HorizontalLayout::Button("Button 1##left");
//        HorizontalLayout::Button("Button 2##left");
//        HorizontalLayout::Button("Button 3##left");
//
//        HorizontalLayout::NextColumn();
//
//        // 第二列：居中对齐
//        HorizontalLayout::Button("Button 1##center");
//        HorizontalLayout::Button("Button 2##center");
//        HorizontalLayout::Button("Button 3##center");
//
//        HorizontalLayout::NextColumn();
//
//        // 第三列：右对齐
//        HorizontalLayout::Button("Button 1##right");
//        HorizontalLayout::Button("Button 2##right");
//        HorizontalLayout::Button("Button 3##right");
//
//        HorizontalLayout::End();


        // 创建三列
        ImGui::Columns(3, "mycolumns");
//        static GLuint myTexture =0;
//        if(myTexture<=0){
//            myTexture = Texture2d::LoadTextureFromFile("path/to/a.png");
//        }

        // 第一列：左对齐
        //ImGui::ImageButton("1");
        //ImGui::SameLine();
        ImGui::Button("2");
        ImGui::SameLine();
        ImGui::Button("3");
        ImGui::SameLine();
        // 移动到下一列
        ImGui::NextColumn();

        // 第二列：居中对齐
        float columnWidth = ImGui::GetColumnWidth();
        float buttonWidth = 100.0f; // 按钮宽度
        float padding = (columnWidth - buttonWidth) / 2.0f;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding); // 设置X位置
        ImGui::Button("4");
        ImGui::SameLine();
        ImGui::Button("5");
        ImGui::SameLine();
        ImGui::Button("6");
        ImGui::SameLine();
        // 移动到下一列
        ImGui::NextColumn();

        // 第三列：右对齐
        float rightPadding = columnWidth - buttonWidth;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + rightPadding); // 设置X位置
        ImGui::Button("7");
        ImGui::SameLine();
        ImGui::Button("8");
        ImGui::SameLine();
        ImGui::Button("9");
        ImGui::SameLine();

        // 结束窗口
        ImGui::Columns(1);

        ImGui::Separator();

    }
}// DivineBrush::Editor