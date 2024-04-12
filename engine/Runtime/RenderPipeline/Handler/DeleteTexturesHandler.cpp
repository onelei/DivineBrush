//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "DeleteTexturesHandler.h"
#include "../RenderPipeline.h"

namespace DivineBrush {
    void DeleteTexturesHandler::Run() {
        RenderCommandHandler::Run();
        auto texture_id_array = new GLuint[textureCount];
        for (int i = 0; i < textureCount; ++i) {
            texture_id_array[i] = RenderPipeline::GetInstance().GetRenderProgramGenerater()->GetTexture(
                    textureHandleArray[i]);
        }
        glDeleteTextures(textureCount, texture_id_array);
        delete[] texture_id_array;
    }
} // DivineBrush