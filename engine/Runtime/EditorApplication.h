//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_EDITORAPPLICATION_H
#define ENGINE_EDITORAPPLICATION_H

#include "Render/MeshRenderer.h"
#include "RenderPipeline/RenderPipeline.h"
#include "Application.h"

namespace DivineBrush {
    class Application;

    class EditorApplication {
    public:
        static int Init();

        static void InitImGui();

        static void Run();

        static void Update();

        static void FixUpdate();

    private:
        static void UpdateScreenSize();

        static GLFWwindow *gameWindow;
        static GLFWwindow *editorWindow;
        static bool useImGui;
    };

} // DivineBrush

#endif //ENGINE_EDITORAPPLICATION_H
