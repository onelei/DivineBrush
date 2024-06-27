//
// Created by onelei on 2024/6/14.
//

#include "BindMeshHandler.h"
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"
#include "../../Render/UniformBufferManager.h"

namespace DivineBrush {
    BindMeshHandler::BindMeshHandler() {
        renderCommand = DivineBrush::RenderCommand::BindMesh;
    }

    BindMeshHandler::~BindMeshHandler() {

    }

    void BindMeshHandler::Run() {
        RenderCommandHandler::Run();
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshFilter::Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex), (void*)offsetof(MeshFilter::Vertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex), (void*)offsetof(MeshFilter::Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex), (void*)offsetof(MeshFilter::Vertex, uv));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void BindMeshHandler::Clear() {
        RenderCommandHandler::Clear();
        DivineBrush::ObjectPool<DivineBrush::BindMeshHandler>::Release(this);
    }
} // DivineBrush