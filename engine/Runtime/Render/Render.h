//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include "MeshRender.h"

namespace DivineBrush {

    class Render {
    public:
        Render() = default;

        ~Render() = default;

    public:
        int Init();

        void InitImGui();

        void Run();

        void Update();

    private:
        GLFWwindow *window;
        static bool useImGui;
    };

} // DivineBrush

#endif //ENGINE_RENDER_H
