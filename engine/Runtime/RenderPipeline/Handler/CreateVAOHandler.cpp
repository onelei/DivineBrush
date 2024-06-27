//
// Created by onelei on 2024/4/11.
//

#include "CreateVAOHandler.h"
#include <GL/glew.h>
#include "../../../depends/template/ObjectPool.h"
#include "../RenderGenerater.h"
#include "../../Render/MeshFilter.h"

namespace DivineBrush {
    CreateVAOHandler::CreateVAOHandler() {
        renderCommand = DivineBrush::RenderCommand::CreateVAO;
    }

    CreateVAOHandler::~CreateVAOHandler() {

    }

    void CreateVAOHandler::Run() {
        RenderCommandHandler::Run();

        // Get shader program ID
        auto program_id = RenderGenerater::GetShader(shaderProgramHandle);
        auto vpos_location = glGetAttribLocation(program_id, "a_pos");
        auto vcol_location = glGetAttribLocation(program_id, "a_color");
        auto a_uv_location = glGetAttribLocation(program_id, "a_uv");
        auto vnormal_location = glGetAttribLocation(program_id, "a_normal");

        // Create VBO and EBO, set VAO
        GLuint kVBO, kEBO;
        GLuint kVAO;

        // Generate and bind VBO
        glGenBuffers(1, &kVBO);
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);
        // Upload vertex data to VBO
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
        RenderGenerater::SetVBO(vboHandle, kVBO);

        // Generate and bind EBO
        glGenBuffers(1, &kEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
        // Upload index data to EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndexDataSize, vertexIndexData, GL_STATIC_DRAW);

        // Generate and bind VAO
        glGenVertexArrays(1, &kVAO);
        glBindVertexArray(kVAO);
        {
            // Bind VBO and set vertex attribute pointers
            glBindBuffer(GL_ARRAY_BUFFER, kVBO);
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex),
                                  (void *) offsetof(MeshFilter::Vertex, pos));
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex),
                                  (void *) offsetof(MeshFilter::Vertex, color));
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex),
                                  (void *) offsetof(MeshFilter::Vertex, uv));
            glVertexAttribPointer(vnormal_location, 3, GL_FLOAT, GL_FALSE, sizeof(MeshFilter::Vertex),
                                  (void *) offsetof(MeshFilter::Vertex, normal));

            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray(vcol_location);
            glEnableVertexAttribArray(a_uv_location);
            glEnableVertexAttribArray(vnormal_location);

            // Bind EBO
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        RenderGenerater::SetVAO(vaoHandle, kVAO);
    }

    void CreateVAOHandler::Clear() {
        RenderCommandHandler::Clear();
        free(vertexData);
        free(vertexIndexData);
        DivineBrush::ObjectPool<DivineBrush::CreateVAOHandler>::Release(this);
    }
} // DivineBrush