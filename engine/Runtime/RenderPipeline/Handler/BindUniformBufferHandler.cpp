//
// Created by onelei on 2024/5/24.
//

#include "BindUniformBufferHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"
#include "../../Render/UniformBufferManager.h"

namespace DivineBrush {
    BindUniformBufferHandler::BindUniformBufferHandler() {
        renderCommand = DivineBrush::RenderCommand::BindUniformBuffer;
    }

    BindUniformBufferHandler::~BindUniformBufferHandler() {

    }

    void BindUniformBufferHandler::Run() {
        RenderCommandHandler::Run();
        auto shaderProgramId = RenderGenerater::GetShader(shaderProgramHandle);
        UniformBufferManager::Bind(shaderProgramId);
    }

    void BindUniformBufferHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::BindUniformBufferHandler>::Release(this);
    }
} // DivineBrush