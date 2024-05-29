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
#include "ProjectWindow.h"
#include "ConsoleWindow.h"
#include "Layouts/DefaultLayout.h"

namespace DivineBrush::Editor {
    bool EditorWindow::is_init = false;
    std::unordered_map<std::string, EditorWindow *> EditorWindow::window_map;
    int EditorWindow::screenWidth = 0;
    int EditorWindow::screenHeight = 0;
    ImGuiIO *EditorWindow::imGuiIO = nullptr;
    BaseLayout* EditorWindow::layout = nullptr;

    EditorWindow::EditorWindow() = default;

    EditorWindow::EditorWindow(const char *_title) {
        this->title = _title;
        layout = new DefaultLayout();
    }

    EditorWindow::~EditorWindow() {
        for (auto &pair: window_map) {
            delete pair.second;
        }
        window_map.clear();
    }

    void EditorWindow::GUI(ImGuiIO *io) {
        if (!is_init) {
            imGuiIO = io;
            window_map[k_Hierarchy] = new HierarchyWindow();
            window_map[k_Inspector] = new InspectorWindow();
            window_map[k_Scene] = new SceneWindow();
            window_map[k_Game] = new GameWindow();
            window_map[k_Project] = new ProjectWindow();
            window_map[k_Console] = new ConsoleWindow();
            is_init = true;
        }
        layout->GUI(io);
    }

    void EditorWindow::OnAwake() {

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

    bool EditorWindow::ContainsWindow(const char *title) {
        return window_map.find(title) != window_map.end();
    }

    EditorWindow *EditorWindow::GetWindow(const char *title) {
        if (ContainsWindow(title)) {
            return window_map[title];
        }
        return nullptr;
    }

    EditorWindow *EditorWindow::CreateWindow(const char *title) {
        auto editorWindow = new EditorWindow(title);
        return CreateWindow(editorWindow);
    }

    EditorWindow *EditorWindow::CreateWindow(EditorWindow *editorWindow) {
        window_map[editorWindow->GetTitle()] = editorWindow;
        return editorWindow;
    }

    void EditorWindow::SetScreen(int width, int height) {
        screenWidth = width;
        screenHeight = height;
    }
}
// DivineBrush