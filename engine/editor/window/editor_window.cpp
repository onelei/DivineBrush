//
// Created by onelei on 2024/3/1.
//

#include <string>
#include <unordered_map>
#include "editor_window.h"
#include "hierarchy/hierarchy_window.h"
#include "inspector/inspector_window.h"
#include "scene/scene_window.h"
#include "game/game_window.h"
#include "project/project_window.h"
#include "console/console_window.h"

namespace DivineBrush::Editor {
    std::unordered_map<char *, EditorWindow *> EditorWindow::_window_map;

    EditorWindow::EditorWindow() = default;

    EditorWindow::EditorWindow(char *title) {
        this->_title = title;
    }

    EditorWindow::~EditorWindow() {
        for (auto &pair: _window_map) {
            delete pair.second;
        }
        _window_map.clear();
    }

    void EditorWindow::GUI() {
        ImGui::Begin(this->GetTitle(), nullptr, ImGuiWindowFlags_NoCollapse);
        OnGUI();
        ImGui::End();
    }

    void EditorWindow::OnEnable() {

    }

    void EditorWindow::OnDisable() {

    }

    void EditorWindow::OnGUI() {

    }

    void EditorWindow::OnDestroy() {

    }

    bool EditorWindow::ContainsWindow(char *title) {
        return _window_map.find(title) != _window_map.end();
    }

    EditorWindow *EditorWindow::GetHierarchyWindow() {
        if (ContainsWindow(k_Hierarchy)) {
            return _window_map[k_Hierarchy];
        }
        auto *window = new HierarchyWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }

    EditorWindow *EditorWindow::GetInspectorWindow() {
        if (ContainsWindow(k_Inspector)) {
            return _window_map[k_Inspector];
        }
        auto *window = new InspectorWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }

    EditorWindow *EditorWindow::GetSceneWindow() {
        if (ContainsWindow(k_Scene)) {
            return _window_map[k_Scene];
        }
        auto *window = new SceneWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }

    EditorWindow *EditorWindow::GetGameWindow() {
        if (ContainsWindow(k_Game)) {
            return _window_map[k_Game];
        }
        auto *window = new GameWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }

    EditorWindow *EditorWindow::GetProjectWindow() {
        if (ContainsWindow(k_Project)) {
            return _window_map[k_Project];
        }
        auto *window = new ProjectWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }

    EditorWindow *EditorWindow::GetConsoleWindow() {
        if (ContainsWindow(k_Console)) {
            return _window_map[k_Console];
        }
        auto *window = new ConsoleWindow();
        return CreateWindow(dynamic_cast<EditorWindow *>(window));
    }


    EditorWindow *EditorWindow::GetWindow(char *title) {
        if (ContainsWindow(title)) {
            return _window_map[title];
        }
        return CreateWindow(title);
    }

    EditorWindow *EditorWindow::CreateWindow(char *title) {
        auto editorWindow = new EditorWindow(title);
        return CreateWindow(editorWindow);
    }

    EditorWindow *EditorWindow::CreateWindow(EditorWindow *editorWindow) {
        _window_map[editorWindow->GetTitle()] = editorWindow;
        return editorWindow;
    }

}
// DivineBrush