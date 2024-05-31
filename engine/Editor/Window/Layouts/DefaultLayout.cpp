//
// Created by onelei on 2024/5/28.
//

#include "DefaultLayout.h"
#include "../EditorWindow.h"

namespace DivineBrush ::Editor {

    void DefaultLayout::OnBeginDockSpace() {
        BaseLayout::OnBeginDockSpace();
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        auto pos = viewport->Pos;
        auto size = viewport->Size;
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGuiWindowFlags window_flags =
                ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        {
            ImGui::PopStyleVar(2);

            // TopBar
            auto topBarWindow = EditorWindow::GetWindow(k_TopBar);
            topBarWindow->OnGUI();

            // Draw dockspace
            dockspaceId = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

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
        //ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.08f, nullptr, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_id_center = dock_main_id;

        // Dock windows
        //ImGui::DockBuilderDockWindow(k_TopBar, dock_id_top);
        ImGui::DockBuilderDockWindow(k_Hierarchy, dock_id_left);
        ImGui::DockBuilderDockWindow(k_Inspector, dock_id_right);
        ImGui::DockBuilderDockWindow(k_Scene, dock_id_center);
        ImGui::DockBuilderDockWindow(k_Game, dock_id_center);
        ImGui::DockBuilderDockWindow(k_Project, dock_id_bottom);
        ImGui::DockBuilderDockWindow(k_Console, dock_id_bottom);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    void DefaultLayout::OnGUI(ImGuiIO *io) {
        ImGuiWindowFlags imGuiWindowFlags = ImGuiWindowFlags_MenuBar;

        // Hierarchy
        auto hierarchyWindow = EditorWindow::GetWindow(k_Hierarchy);
        if (hierarchyWindow != nullptr) {
            ImGui::Begin(hierarchyWindow->GetTitle());
            hierarchyWindow->size = ImGui::GetWindowSize();
            hierarchyWindow->pos = ImGui::GetWindowPos();
            hierarchyWindow->OnGUI();
            ImGui::End();
        }

        // Scene
        auto sceneWindow = EditorWindow::GetWindow(k_Scene);
        if (sceneWindow != nullptr) {
            ImGui::Begin(sceneWindow->GetTitle(), nullptr, imGuiWindowFlags);
            sceneWindow->size = ImGui::GetWindowSize();
            sceneWindow->pos = ImGui::GetWindowPos();
            sceneWindow->OnGUI();
            ImGui::End();
        }

        // Game
        auto gameWindow = EditorWindow::GetWindow(k_Game);
        if (gameWindow != nullptr) {
            ImGui::Begin(gameWindow->GetTitle(), nullptr, imGuiWindowFlags);
            gameWindow->size = ImGui::GetWindowSize();
            gameWindow->pos = ImGui::GetWindowPos();
            gameWindow->OnGUI();
            ImGui::End();
        }

        // Inspector
        auto inspectorWindow = EditorWindow::GetWindow(k_Inspector);
        if (inspectorWindow != nullptr) {
            ImGui::Begin(inspectorWindow->GetTitle());
            inspectorWindow->size = ImGui::GetWindowSize();
            inspectorWindow->pos = ImGui::GetWindowPos();
            inspectorWindow->OnGUI();
            ImGui::End();
        }

        // Project
        auto projectWindow = EditorWindow::GetWindow(k_Project);
        if (projectWindow != nullptr) {
            ImGui::Begin(projectWindow->GetTitle());
            projectWindow->size = ImGui::GetWindowSize();
            projectWindow->pos = ImGui::GetWindowPos();
            projectWindow->OnGUI();
            ImGui::End();
        }

        // Console
        auto consoleWindow = EditorWindow::GetWindow(k_Console);
        if (consoleWindow != nullptr) {
            ImGui::Begin(consoleWindow->GetTitle());
            consoleWindow->size = ImGui::GetWindowSize();
            consoleWindow->pos = ImGui::GetWindowPos();
            consoleWindow->OnGUI();
            ImGui::End();
        }

    }

} // DivineBrush
