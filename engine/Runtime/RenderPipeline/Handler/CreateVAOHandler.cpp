//
// Created by onelei on 2024/4/11.
//

#include "CreateVAOHandler.h"

namespace DivineBrush {
    void CreateVAOHandler::Run() {
        RenderCommandHandler::Run();
        auto vpos_location = glGetAttribLocation(program_id, "a_pos");
        auto vcol_location = glGetAttribLocation(program_id, "a_color");
        auto a_uv_location = glGetAttribLocation(program_id, "a_uv");

        //创建VBO和EBO，设置VAO
        //在GPU上创建缓冲区对象
        glGenBuffers(1, &kVBO);
        //将缓冲区对象指定为顶点缓冲区对象
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);
        //上传顶点数据到缓冲区对象
        glBufferData(GL_ARRAY_BUFFER, mesh_filter->GetMesh()->vertex_num * sizeof(MeshFilter::Vertex),
                     mesh_filter->GetMesh()->vertex_data, GL_STATIC_DRAW);

        //在GPU上创建缓冲区对象
        glGenBuffers(1, &kEBO);
        //将缓冲区对象指定为顶点索引缓冲区对象
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
        //上传顶点索引数据到缓冲区对象
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->GetMesh()->vertex_index_num * sizeof(unsigned short),
                     mesh_filter->GetMesh()->vertex_index_data, GL_STATIC_DRAW);
        //设置VAO
        glGenVertexArrays(1, &kVAO);
        glBindVertexArray(kVAO);
        {
            //指定当前使用的VBO
            glBindBuffer(GL_ARRAY_BUFFER, kVBO);
            //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(MeshFilter::Vertex), 0);
            //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联。
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(MeshFilter::Vertex),
                                  (void *) (sizeof(float) * 3));
            //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联。
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(MeshFilter::Vertex),
                                  (void *) (sizeof(float) * (3 + 4)));

            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray(vcol_location);
            glEnableVertexAttribArray(a_uv_location);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void CreateVAOHandler::Clear() {
        RenderCommandHandler::Clear();
    }
} // DivineBrush