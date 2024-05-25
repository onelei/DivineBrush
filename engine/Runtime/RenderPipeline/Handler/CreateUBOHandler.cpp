//
// Created by onelei on 2024/5/24.
//

#include "CreateUBOHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    CreateUBOHandler::CreateUBOHandler() {
        renderCommand = DivineBrush::RenderCommand::CreateUBO;
    }

    CreateUBOHandler::~CreateUBOHandler() {

    }

    void CreateUBOHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgramId = RenderGenerater::GetShader(shaderProgramHandle);
        auto index = glGetUniformBlockIndex(shaderProgramId, name);
        GLuint binding = 1;
        glUniformBlockBinding(shaderProgramId, index, binding);

        GLuint uboProgramId;
        glGenBuffers(1, &uboProgramId);
        glBindBuffer(GL_UNIFORM_BUFFER, uboProgramId);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, uboProgramId);
        RenderGenerater::SetUBO(uboHandle, uboProgramId);
    }

    void CreateUBOHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::CreateUBOHandler>::Release(this);
    }
} // DivineBrush