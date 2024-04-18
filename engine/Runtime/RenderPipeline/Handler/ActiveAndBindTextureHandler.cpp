//
// Created by onelei on 2024/4/11.
//

#include "ActiveAndBindTextureHandler.h"
#include "GL/glew.h"
#include "../RenderPipeline.h"
#include "../../template/ObjectPool.h"

namespace DivineBrush {
    void ActiveAndBindTextureHandler::Run() {
        RenderCommandHandler::Run();
        //激活纹理单元
        glActiveTexture(textureUnit);
        //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
        auto textureProgram = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetTexture(textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureProgram);
    }

    void ActiveAndBindTextureHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::ActiveAndBindTextureHandler>::Release(this);
    }
} // DivineBrush