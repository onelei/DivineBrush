//
// Created by onelei on 2024/4/11.
//

#include <GL/glew.h>
#include "DeleteTexturesHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    DeleteTexturesHandler::DeleteTexturesHandler() {
        renderCommand = DivineBrush::RenderCommand::DeleteTextures;
    }

    DeleteTexturesHandler::~DeleteTexturesHandler(){

    }

    void DeleteTexturesHandler::Run() {
        RenderCommandHandler::Run();
        auto texture_id_array = new GLuint[textureCount];
        for (int i = 0; i < textureCount; ++i) {
            texture_id_array[i] = RenderGenerater::GetTexture(
                    textureHandleArray[i]);
        }
        glDeleteTextures(textureCount, texture_id_array);
        delete[] texture_id_array;
    }

    void DeleteTexturesHandler::Clear() {
        RenderCommandHandler::Clear();
        free(textureHandleArray);
        DivineBrush::ObjectPool<DivineBrush::DeleteTexturesHandler>::Release(this);
    }
} // DivineBrush