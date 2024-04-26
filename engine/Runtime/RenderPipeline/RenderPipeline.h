//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_RENDERPIPELINE_H
#define ENGINE_RENDERPIPELINE_H

#include <thread>
#include <GLFW/glfw3.h>
#include "rigtorp/SPSCQueue.h"
#include "../../depends/template/Singleton.h"
#include "Handler/RenderCommandHandler.h"

namespace DivineBrush {

    class RenderPipeline {

    public:
        static void Init(GLFWwindow *window);

        static void Dispose();

        static GLuint GetColorTextureId() {
            return color_texture_id;
        }

        static GLuint GetDepthTextureId() {
            return depth_texture_id;
        }

    private:
        static void Start();

        static void Prepare();

        static GLFWwindow *window;
        static bool isDispose;
        ///FBO 颜色纹理
        static GLuint color_texture_id;
        ///FBO 深度纹理
        static GLuint depth_texture_id;
        static std::thread renderThread;
    };

} // DivineBrush

#endif //ENGINE_RENDERPIPELINE_H
