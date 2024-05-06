//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include "MeshRender.h"
#include "../RenderPipeline/RenderPipeline.h"
#include "../Application.h"

namespace DivineBrush {
    class Application;

    class Render {
    public:
        Render() = default;

        ~Render() = default;

    public:
        int Init();

        void InitImGui();

        void Run();

        void Update();

        void FixUpdate();

    private:
        void UpdateScreenSize();
        GLFWwindow *gameWindow;
        GLFWwindow *editorWindow;
        static bool useImGui;
    };

} // DivineBrush

#endif //ENGINE_RENDER_H
