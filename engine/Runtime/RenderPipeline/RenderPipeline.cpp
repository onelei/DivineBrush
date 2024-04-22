//
// Created by onelei on 2024/4/10.
//

#include <iostream>
#include <GL/glew.h>
#include "RenderPipeline.h"

namespace DivineBrush {

    void RenderPipeline::Init(GLFWwindow *window) {
        this->window = window;
        this->renderThread = std::thread(&RenderPipeline::Start, this);
        this->renderThread.detach();
    }

    void RenderPipeline::Dispose() {
        this->isDispose = true;
        if (this->renderThread.joinable()) {
            this->renderThread.join();
        }
    }

    void RenderPipeline::Prepare() {
        glfwMakeContextCurrent(window);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //绑定FBO进行渲染：在你的渲染循环中，当你想将内容渲染到离屏缓冲区（即FBO）时，你应该先绑定FBO。
        //创建全局FBO，将整个游戏渲染到FBO，提供给编辑器，作为Game视图显示
        GLuint frame_buffer_object_id = 0;
        glGenFramebuffers(1, &frame_buffer_object_id);
        if (frame_buffer_object_id == 0) {
            printf("CreateFBO FBO Error!");
            exit(EXIT_FAILURE);
        }
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer_object_id);
        // 创建颜色纹理并附加到FBO的颜色附着点上
        glGenTextures(1, &color_texture_id);
        glBindTexture(GL_TEXTURE_2D, color_texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture_id, 0);
        // 创建深度-模板纹理并附加到FBO的深度附着点上，并且这个纹理也将用于模板
        glGenTextures(1, &depth_texture_id);
        glBindTexture(GL_TEXTURE_2D, depth_texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 注意这里使用GL_DEPTH24_STENCIL8作为内部格式，并且数据格式改为GL_UNSIGNED_INT_24_8
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL,
                     GL_UNSIGNED_INT_24_8,
                     nullptr);
        // 注意附加到GL_DEPTH_STENCIL_ATTACHMENT
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_texture_id, 0);
        //检测帧缓冲区完整性
        //auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            ///36055 = 0x8CD7 GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 附着点没有东西
            //printf("BindFBO FBO Error,Status:{} !", status);
            exit(EXIT_FAILURE);
        }
        //设置视口和清除缓冲区：设置合适的视口，并且清除颜色和深度缓冲区，为渲染做准备。
        glViewport(0, 0, width, height);
    }

    void RenderPipeline::Start() {
        Prepare();
        while (!isDispose) {
            while (true) {
                if (ringBuffer.empty()) {
                    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
                    continue;
                }
                auto renderCommand = (*ringBuffer.front());
                auto isWait = renderCommand->GetIsWait();
                auto commandType = renderCommand->GetRenderCommand();
                if (commandType != DivineBrush::RenderCommand::None) {
                    renderCommand->Run();
                }
                ringBuffer.pop();
                if (!isWait) {
                    renderCommand->Clear();
                }

                if (commandType == DivineBrush::RenderCommand::EndFrame) {
                    break;
                }
            }
            std::cout << "task in queue:" << ringBuffer.size() << std::endl;
        }
    }


} // DivineBrush