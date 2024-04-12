//
// Created by onelei on 2024/4/10.
//

#include <iostream>
#include "RenderPipeline.h"

namespace DivineBrush {

    RenderPipeline::RenderPipeline() : ringBuffer(1024) {

    }

    RenderPipeline::~RenderPipeline() {

    }

    void RenderPipeline::Init(GLFWwindow *window) {
        this->window = window;
        this->renderProgramGenerater = new RenderProgramGenerater();
        this->renderThread = std::thread(&RenderPipeline::Start, this);
        this->renderThread.detach();
    }

    void RenderPipeline::Dispose() {
        if (this->renderThread.joinable()) {
            this->renderThread.join();
        }
    }

    void RenderPipeline::Start() {
        while (!glfwWindowShouldClose(window)) {
            while (true) {
                if (ringBuffer.IsEmpty()) {
                    continue;
                }
                auto renderCommand = ringBuffer.Peek();
                renderCommand->Run();
                ringBuffer.Dequeue();
                if (renderCommand->renderCommand == RenderCommand::EndFrame) {
                    break;
                }
            }
            //std::cout<<"task in queue:"<<RenderTaskQueue::Size()<<std::endl;
        }
    }

} // DivineBrush