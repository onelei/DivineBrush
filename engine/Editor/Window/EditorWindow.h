//
// Created by onelei on 2024/3/1.
//

#ifndef ENGINE_EDITORWINDOW_H
#define ENGINE_EDITORWINDOW_H

#include <string>
#include <unordered_map>
#include <imgui_internal.h>
#include "../../Runtime/Serialize/ScriptableObject.h"
#include "Layouts/BaseLayout.h"

namespace DivineBrush::Editor {
    static const char *k_TopBar = "TopBar";
    static const char *k_Hierarchy = "Hierarchy";
    static const char *k_Inspector = "Inspector";
    static const char *k_Scene = "Scene";
    static const char *k_Game = "Game";
    static const char *k_Project = "Project";
    static const char *k_Console = "Console";

    class EditorWindow : public ScriptableObject {
    public:
        EditorWindow();

        EditorWindow(const char *title);

        ~EditorWindow();

        static bool ContainsWindow(const char *title);

        static EditorWindow *GetWindow(const char *title);

        static EditorWindow *CreateWindow(const char *title);

        static EditorWindow *CreateWindow(EditorWindow *editorWindow);

        static void GUI(ImGuiIO *io);

        static void SetScreen(int width, int height);

        static int GetScreenWidth() {
            return screenWidth;
        }

        static int GetScreenHeight() {
            return screenHeight;
        };

        static ImGuiIO *GetIO() {
            return imGuiIO;
        }

        virtual const char *GetTitle() {
            return this->title;
        };

        ImVec2 GetSize() const {
            return this->size;
        }

        virtual void OnAwake();

        virtual void OnEnable();

        virtual void OnDisable();

        virtual void OnGUI();

        virtual void OnResize();

        virtual void OnDestroy();

    public:
        //window title
        const char *title;
        ImVec2 pos;
        //window size
        ImVec2 size;
        ImGuiWindow *guiWindow;

    private:
        static bool is_init;
        static std::unordered_map<std::string, EditorWindow *> window_map;
        static int screenWidth;
        static int screenHeight;
        static ImGuiIO *imGuiIO;
        static BaseLayout *layout;
    };
} // DivineBrush

#endif //ENGINE_EDITORWINDOW_H
