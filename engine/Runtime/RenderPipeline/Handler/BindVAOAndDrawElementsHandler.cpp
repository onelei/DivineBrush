//
// Created by onelei on 2024/4/11.
//

#include "BindVAOAndDrawElementsHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"

namespace DivineBrush {
    BindVAOAndDrawElementsHandler::BindVAOAndDrawElementsHandler() {
        renderCommand = DivineBrush::RenderCommand::BindVAOAndDrawElements;
    }

    BindVAOAndDrawElementsHandler::~BindVAOAndDrawElementsHandler() {

    }

    void BindVAOAndDrawElementsHandler::Run() {
        RenderCommandHandler::Run();
        auto kVAO = RenderGenerater::GetVAO(vaoHandle);
        glBindVertexArray(kVAO);
        {
            //使用顶点索引进行绘制，最后的0表示数据偏移量。
            glDrawElements(GL_TRIANGLES, vertexIndexCount, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }

    void BindVAOAndDrawElementsHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::BindVAOAndDrawElementsHandler>::Release(this);
    }
} // DivineBrush