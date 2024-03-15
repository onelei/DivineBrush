//
// Created by onelei on 2024/3/15.
//

#include "mesh_render.h"

namespace DivineBrush {

    void MeshRender::Prepare() {
        //获取Shader中的变量
        auto shader = material->GetShader();
        program_id = shader->GetProgramId();
        mvp_location = glGetUniformLocation(program_id, "u_mvp");
        vpos_location = glGetAttribLocation(program_id, "a_pos");
        vcol_location = glGetAttribLocation(program_id, "a_color");
        a_uv_location = glGetAttribLocation(program_id, "a_uv");

        glGenVertexArrays(1, &kVAO);
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

    void MeshRender::Render() {
        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program_id);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除
            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
            //拿到保存的Texture
            auto textures = material->GetTextures();
            for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
                GLint u_texture_location = glGetUniformLocation(program_id,
                                                                textures[texture_index].first.c_str());
                //激活纹理单元0
                glActiveTexture(GL_TEXTURE0 + texture_index);
                //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
                glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->gl_texture_id);
                //设置Shader程序从纹理单元0读取颜色数据
                glUniform1i(u_texture_location, texture_index);
            }

            glBindVertexArray(kVAO);
            {
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
            }
            glBindVertexArray(0);
        }
    }

} // DivineBrush