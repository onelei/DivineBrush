//
// Created by onelei on 2024/3/1.
//

#ifndef ENGINE_EDITOR_WINDOW_H
#define ENGINE_EDITOR_WINDOW_H

#include "../../runtime/serialization/scriptable_object.h"
#include <string>
#include <unordered_map>

namespace DivineBrush::Editor {
    class HierarchyWindow;
}

namespace DivineBrush::Editor {
    static char* k_Hierarchy = "Hierarchy";
    static char* k_Inspector = "Inspector";
    static char* k_Scene = "Scene";
    static char* k_Game = "Game";
    static char* k_Project = "Project";
    static char* k_Console = "Console";

    class EditorWindow : public ScriptableObject {
    public:
        EditorWindow();

        EditorWindow(char *title);

        ~EditorWindow();

        static bool ContainsWindow(char *title);

        static EditorWindow *GetHierarchyWindow();

        static EditorWindow *GetInspectorWindow();

        static EditorWindow *GetSceneWindow();

        static EditorWindow *GetGameWindow();

        static EditorWindow *GetProjectWindow();

        static EditorWindow *GetConsoleWindow();

        static EditorWindow *GetWindow(char *title);

        static EditorWindow *CreateWindow(char *title);

        static EditorWindow *CreateWindow(EditorWindow *editorWindow);

        virtual char *GetTitle() {
            return this->_title;
        };

        void GUI();

        virtual void OnEnable();

        virtual void OnDisable();

        virtual void OnGUI();

        virtual void OnDestroy();

    public:
        char *_title;
    private:
        static std::unordered_map<char *, EditorWindow *> _window_map;
    };
} // DivineBrush

#endif //ENGINE_EDITOR_WINDOW_H
