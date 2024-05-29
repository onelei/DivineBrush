//
// Created by onelei on 2024/5/28.
//

#include "DefaultLayout.h"
#include "../EditorWindow.h"

namespace DivineBrush ::Editor {

    void DefaultLayout::OnBeginDockSpace() {
        BaseLayout::OnBeginDockSpace();
        // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGuiWindowFlags window_flags =
                ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar(2);

        dockspaceId = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        // 创建菜单栏
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

        ImGui::End();
    }

    void DefaultLayout::OnInitLayout() {
        BaseLayout::OnInitLayout();
        ImGui::DockBuilderRemoveNode(dockspaceId); // Clear any previous layout
        ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);

        // Split the dockspace into 4 nodes
        ImGuiID dock_main_id = dockspaceId;
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_center = dock_main_id;

        // Dock windows
        ImGui::DockBuilderDockWindow(k_Hierarchy, dock_id_left);
        ImGui::DockBuilderDockWindow(k_Inspector, dock_id_right);
        ImGui::DockBuilderDockWindow("Scene and Game", dock_id_center);
        ImGui::DockBuilderDockWindow("Project and Console", dock_id_bottom);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    void DefaultLayout::OnGUI(ImGuiIO *io) {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_NoTooltip;
        ImGuiTabItemFlags tabItemFlags = ImGuiTabItemFlags_NoTooltip;
        //ImGuiDockNodeFlags nodeFlags = ImGuiDockNodeFlags_AutoHideTabBar;
        // Hierarchy
        auto hierarchyWindow = EditorWindow::GetWindow(k_Hierarchy);
        if (hierarchyWindow != nullptr) {
            ImGui::Begin(hierarchyWindow->GetTitle());
            hierarchyWindow->size = ImGui::GetWindowSize();
            hierarchyWindow->pos = ImGui::GetWindowPos();
            hierarchyWindow->OnGUI();
            ImGui::End();
        }

        ImGui::Begin("Scene and Game", nullptr, windowFlags);
        {
            if (ImGui::BeginTabBar("##Tabs",tabBarFlags)) {
                // Scene
                auto sceneWindow = EditorWindow::GetWindow(k_Scene);
                if (sceneWindow != nullptr) {
                    if (ImGui::BeginTabItem(sceneWindow->GetTitle(), nullptr,tabItemFlags)) {
                        sceneWindow->size = ImGui::GetWindowSize();
                        sceneWindow->pos = ImGui::GetWindowPos();
                        sceneWindow->OnGUI();
                        ImGui::EndTabItem();
                    }
                }
                // Game
                auto gameWindow = EditorWindow::GetWindow(k_Game);
                if (gameWindow != nullptr) {
                    if (ImGui::BeginTabItem(gameWindow->GetTitle(), nullptr,tabItemFlags)) {
                        gameWindow->size = ImGui::GetWindowSize();
                        gameWindow->pos = ImGui::GetWindowPos();
                        gameWindow->OnGUI();
                        ImGui::EndTabItem();
                    }
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();



        // Inspector
        auto inspectorWindow = EditorWindow::GetWindow(k_Inspector);
        if (inspectorWindow != nullptr) {
            ImGui::Begin(inspectorWindow->GetTitle());
            inspectorWindow->size = ImGui::GetWindowSize();
            inspectorWindow->pos = ImGui::GetWindowPos();
            inspectorWindow->OnGUI();
            ImGui::End();
        }

        ImGui::Begin("Project and Console", nullptr, windowFlags);
        {
            if (ImGui::BeginTabBar("##Tabs",tabBarFlags)) {
                // Project
                auto projectWindow = EditorWindow::GetWindow(k_Project);
                if (projectWindow != nullptr) {
                    if (ImGui::BeginTabItem(projectWindow->GetTitle())) {
                        projectWindow->size = ImGui::GetWindowSize();
                        projectWindow->pos = ImGui::GetWindowPos();
                        projectWindow->OnGUI();
                        ImGui::EndTabItem();
                    }
                }

                // Console
                auto consoleWindow = EditorWindow::GetWindow(k_Console);
                if (consoleWindow != nullptr) {
                    if (ImGui::BeginTabItem(consoleWindow->GetTitle())) {
                        consoleWindow->size = ImGui::GetWindowSize();
                        consoleWindow->pos = ImGui::GetWindowPos();
                        consoleWindow->OnGUI();
                        ImGui::EndTabItem();
                    }
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }

} // DivineBrush
