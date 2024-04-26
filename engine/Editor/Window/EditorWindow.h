//
// Created by onelei on 2024/3/1.
//

#ifndef ENGINE_EDITORWINDOW_H
#define ENGINE_EDITORWINDOW_H

#include <string>
#include <unordered_map>
#include <imgui.h>
#include "../../Runtime/Serialize/ScriptableObject.h"

namespace DivineBrush::Editor {
    class HierarchyWindow;
}

namespace DivineBrush::Editor {
    static std::string k_Hierarchy = "Hierarchy";
    static std::string k_Inspector = "Inspector";
    static std::string k_Scene = "Scene";
    static std::string k_Game = "Game";
    static std::string k_Project = "Project";
    static std::string k_Console = "Console";

    class EditorWindow : public ScriptableObject {
    public:
        EditorWindow();

        EditorWindow(std::string title);

        ~EditorWindow();

        static bool ContainsWindow(std::string title);

        static EditorWindow *GetWindow(const std::string& title);

        static EditorWindow *CreateWindow(std::string title);

        static EditorWindow *CreateWindow(EditorWindow *editorWindow);

        static void GUI();

        virtual std::string GetTitle() {
            return this->title;
        };

        ImVec2 GetSize() const {
            return this->size;
        }

        virtual void OnEnable();

        virtual void OnDisable();

        virtual void OnGUI();

        virtual void OnResize();

        virtual void OnDestroy();

    public:
        //window title
        std::string title;
        ImVec2 position;
        //window size
        ImVec2 size;
    private:
        static bool is_init;
        static std::unordered_map<std::string, EditorWindow *> window_map;
    };
} // DivineBrush

#endif //ENGINE_EDITORWINDOW_H
