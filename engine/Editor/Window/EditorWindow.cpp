//
// Created by onelei on 2024/3/1.
//

#include <string>
#include <unordered_map>
#include <utility>
#include "EditorWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"
#include "SceneWindow.h"
#include "GameWindow.h"
#include "project_window.h"
#include "ConsoleWindow.h"

namespace DivineBrush::Editor {
    bool EditorWindow::is_init = false;
    std::unordered_map<std::string, EditorWindow *> EditorWindow::window_map;

    EditorWindow::EditorWindow() = default;

    EditorWindow::EditorWindow(std::string _title) {
        this->title = std::move(_title);
    }

    EditorWindow::~EditorWindow() {
        for (auto &pair: window_map) {
            delete pair.second;
        }
        window_map.clear();
    }

    void EditorWindow::GUI() {
        if(!is_init) {
            window_map[k_Hierarchy] = new HierarchyWindow();
            window_map[k_Inspector] = new InspectorWindow();
            window_map[k_Scene] = new SceneWindow();
            window_map[k_Game] = new GameWindow();
            window_map[k_Project] = new ProjectWindow();
            window_map[k_Console] = new ConsoleWindow();
            is_init = true;
        }

        for (auto &pair: window_map) {
            ImGui::Begin(pair.second->GetTitle().c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
            //pair.second-> OnResize();
            pair.second->OnGUI();
            ImGui::End();
        }
    }

    void EditorWindow::OnEnable() {

    }

    void EditorWindow::OnDisable() {

    }

    void EditorWindow::OnGUI() {

    }

    void EditorWindow::OnResize() {

    }

    void EditorWindow::OnDestroy() {

    }

    bool EditorWindow::ContainsWindow(std::string title) {
        return window_map.find(title) != window_map.end();
    }

    EditorWindow *EditorWindow::GetWindow(const std::string& title) {
        if (ContainsWindow(title)) {
            return window_map[title];
        }
        return CreateWindow(title);
    }

    EditorWindow *EditorWindow::CreateWindow(std::string title) {
        auto editorWindow = new EditorWindow(std::move(title));
        return CreateWindow(editorWindow);
    }

    EditorWindow *EditorWindow::CreateWindow(EditorWindow *editorWindow) {
        window_map[editorWindow->GetTitle()] = editorWindow;
        return editorWindow;
    }

}
// DivineBrush