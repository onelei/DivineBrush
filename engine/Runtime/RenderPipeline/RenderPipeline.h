//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_RENDERPIPELINE_H
#define ENGINE_RENDERPIPELINE_H

#include <GLFW/glfw3.h>
#include <thread>
#include "Handler/RenderCommandHandler.h"
#include "../../depends/template/RingBuffer.h"
#include "RenderProgramGenerater.h"
#include "../../depends/template/Singleton.h"

namespace DivineBrush {

    class RenderPipeline : public Singleton<RenderPipeline> {
        friend class Singleton<RenderPipeline>; // 确保SingletonTemplate可以访问MyClass的构造函数
    protected:
        RenderPipeline();
        ~RenderPipeline();
    public:
        void Init(GLFWwindow *window);

        void Dispose();

        RenderProgramGenerater *GetRenderProgramGenerater() {
            return renderProgramGenerater;
        }

        void AddRenderCommandHandler(RenderCommandHandler *handler){
            ringBuffer.Enqueue(handler);
        }

    private:
        void Start();

        GLFWwindow *window = nullptr;//RenderCommandHandler *handler
        std::thread renderThread;
        RingBuffer<RenderCommandHandler *> ringBuffer;
        RenderProgramGenerater *renderProgramGenerater = nullptr;
    };

} // DivineBrush

#endif //ENGINE_RENDERPIPELINE_H
