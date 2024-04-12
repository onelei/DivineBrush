//
// Created by onelei on 2024/4/11.
//

#include "CreateTexImage2DHandler.h"
#include <GL/glew.h>
#include "../RenderPipeline.h"

namespace DivineBrush {
    void CreateTexImage2DHandler::Run() {
        RenderCommandHandler::Run();
        GLuint gl_texture_id;
        //1. 通知显卡创建纹理对象，返回句柄;
        glGenTextures(1, &(gl_texture_id));
        //2. 将纹理绑定到特定纹理目标;
        glBindTexture(GL_TEXTURE_2D, gl_texture_id);
        //3. 将图片rgb数据上传到GPU;
        glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, width, height, 0,
                     clientFormat, dataType, data);
        //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        RenderPipeline::GetInstance().GetRenderProgramGenerater()->SetTexture(textureHandle, gl_texture_id);
    }

    void CreateTexImage2DHandler::Clear() {
        RenderCommandHandler::Clear();
    }
} // DivineBrush