//
// Created by onelei on 2024/5/17.
//

#include "UpdateUBODataHandler.h"
#include <GL/glew.h>
#include "../../../depends/template/ObjectPool.h"
#include "../../Render/UniformBufferManager.h"

namespace DivineBrush {
    UpdateUBODataHandler::UpdateUBODataHandler() {
        renderCommand = DivineBrush::RenderCommand::UpdateUBOData;
    }

    UpdateUBODataHandler::~UpdateUBODataHandler() {
        free(data);
    }

    void UpdateUBODataHandler::Run() {
        RenderCommandHandler::Run();
        UniformBuffer *uniformBuffer = nullptr;
        if (UniformBufferManager::TryGetUniformBuffer(name, uniformBuffer)) {
            glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer->buffer);
            std::vector<UniformInfo> *uniformInfos = nullptr;
            if (UniformBufferManager::TryGetUniformInfos(memberName, uniformInfos)) {
                for (auto &uniformInfo: *uniformInfos) {
                    glBufferSubData(GL_UNIFORM_BUFFER, uniformInfo.offset, uniformInfo.size, data);
                }
            }
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

    }

    void UpdateUBODataHandler::Clear() {
        RenderCommandHandler::Clear();
        free(data);
        DivineBrush::ObjectPool<DivineBrush::UpdateUBODataHandler>::Release(this);
    }
} // DivineBrush