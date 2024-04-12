//
// Created by onelei on 2024/3/15.
//
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "MeshRender.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"
#include "../RenderPipeline/Handler/CreateVAOHandler.h"
#include "../../depends/template/ObjectPool.h"
#include "../RenderPipeline/RenderPipeline.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<MeshRender>("MeshRender")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    void MeshRender::Prepare() {
        //获取Shader中的变量
        auto shader = material->GetShader();
        program_id = shader->GetProgramId();
        auto component_mesh_filter = gameObject->GetComponent("MeshFilter");
        mesh_filter = dynamic_cast<MeshFilter *>(component_mesh_filter);
        if (!mesh_filter) {
            return;
        }
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

        vaoHandle = RenderPipeline::GetInstance().GetRenderProgramGenerater()->CreateVAO();
        vboHandle = RenderPipeline::GetInstance().GetRenderProgramGenerater()->CreateVBO();
        auto handler = ObjectPool<CreateVAOHandler>::Get();
        handler->vaoHandle = vaoHandle;
        handler->vboHandle = vboHandle;
        handler->vertexDataSize = mesh_filter->GetMesh()->vertex_num * sizeof(MeshFilter::Vertex);
        handler->vertexDataCount = mesh_filter->GetMesh()->vertex_num;
        handler->vertexData = mesh_filter->GetMesh()->vertex_data;
        handler->vertexIndexDataSize = mesh_filter->GetMesh()->vertex_index_num * sizeof(unsigned short);
        handler->vertexIndexData = mesh_filter->GetMesh()->vertex_index_data;
        handler->shaderProgramHandle = program_id;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);

    }

    void MeshRender::Render() {
        auto component = gameObject->GetComponent("Transform");
        auto transform = dynamic_cast<Transform *>(component);
        if (!transform) {
            return;
        }
        auto component_mesh_filter = gameObject->GetComponent("MeshFilter");
        mesh_filter = dynamic_cast<MeshFilter *>(component_mesh_filter);
        if (!mesh_filter) {
            return;
        }

        auto camera = Camera::GetCurrentCamera();
        if(camera == nullptr) {
            return;
        }

        //对两个数的位进行逐位的与(AND)操作。如果两个相应的位都为1，则该位的结果为1；否则，为0。
        if ((GetGameObject()->GetLayer() & camera->GetCullingMask()) == 0x00) {
            return;
        }

        if(kVAO == 0){
            Prepare();
        }

        //进行实际的渲染调用：这里你绘制你的场景，包括提到的立方体渲染。
        glm::mat4 trans = glm::translate(transform->GetPosition()); //不移动顶点坐标;

        auto rotation = transform->GetRotation();
        auto eulerAngleYXZ = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x),
                                                glm::radians(rotation.z)); //使用欧拉角旋转;

        auto scale = glm::scale(transform->GetScale()); //缩放;
        auto model = trans * scale * eulerAngleYXZ;

        mvp = camera->GetProjection() * camera->GetView() * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program_id);
        {
            GetGameObject()->ForeachComponent([](Component *component) {
                component->OnPreprocessRender();
            });

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //上传mvp矩阵
            glUniformMatrix4fv(glGetUniformLocation(program_id, "u_mvp"), 1, GL_FALSE, &mvp[0][0]);
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
                glDrawElements(GL_TRIANGLES, mesh_filter->GetMesh()->vertex_index_num, GL_UNSIGNED_SHORT,
                               0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
            }
            glBindVertexArray(0);

            GetGameObject()->ForeachComponent([](Component *component) {
                component->OnPostprocessRender();
            });
        }
    }

} // DivineBrush