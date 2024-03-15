//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include "mesh_render.h"

namespace DivineBrush {

    class Render {
    public:
        Render() = default;

        ~Render() = default;

    public:
        int Init();

        void InitImGui();

        void Run();

    private:
        GLFWwindow *window;
        MeshRender* mesh_render= nullptr;
    };

} // DivineBrush

#endif //ENGINE_RENDER_H
