//
// Created by onelei on 2024/3/15.
//
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "MeshRenderer.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"
#include "../RenderPipeline/RenderGenerater.h"
#include "../RenderPipeline/RenderCommandBuffer.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<MeshRenderer>("MeshRenderer")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    void MeshRenderer::Render() {
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
        if (camera == nullptr) {
            return;
        }

        //对两个数的位进行逐位的与(AND)操作。如果两个相应的位都为1，则该位的结果为1；否则，为0。
        if ((GetGameObject()->GetLayer() & camera->GetCullingMask()) == 0x00) {
            return;
        }
        auto mesh = mesh_filter->GetSkinMesh() != nullptr ? mesh_filter->GetSkinMesh() : mesh_filter->GetMesh();
        //获取Shader中的变量
        auto shader = material->GetShader();
        shaderProgramHandle = shader->GetProgramHandle();
        if (vaoHandle == 0) {
            vaoHandle = RenderGenerater::CreateVAO();
            vboHandle = RenderGenerater::CreateVBO();
            auto vertexDataSize = mesh->vertex_num * sizeof(MeshFilter::Vertex);
            auto vertexTypeSize = sizeof(MeshFilter::Vertex);
            auto vertexData = mesh->vertex_data;
            auto vertexIndexDataSize = mesh->vertex_index_num * sizeof(unsigned short);
            auto vertexIndexData = mesh->vertex_index_data;
            RenderCommandBuffer::CreateVAOHandler(shaderProgramHandle, vaoHandle, vboHandle, vertexDataSize, vertexTypeSize,
                                                  vertexData, vertexIndexDataSize, vertexIndexData);
        } else {
            auto vertexDataSize = mesh->vertex_num * sizeof(MeshFilter::Vertex);
            RenderCommandBuffer::UpdateVBODataHandler(vboHandle, vertexDataSize, mesh->vertex_data);
        }

        //进行实际的渲染调用：这里你绘制你的场景，包括提到的立方体渲染。
        glm::mat4 trans = glm::translate(transform->GetPosition()); //不移动顶点坐标;

        auto rotation = transform->GetRotation();
        auto eulerAngleYXZ = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x),
                                                glm::radians(rotation.z)); //使用欧拉角旋转;

        auto scale = glm::scale(transform->GetScale()); //缩放;
        auto model = trans * scale * eulerAngleYXZ;

        auto mvp = camera->GetProjection() * camera->GetView() * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        shader->Use();

        GetGameObject()->ForeachComponent([](Component *component) {
            component->OnPreprocessRender();
        });

        //GL_DEPTH_TEST:开启深度测试
        SetGLEnabled(GL_DEPTH_TEST, true);
        //GL_CULL_FACE:开启背面剔除
        SetGLEnabled(GL_CULL_FACE, true);
        //GL_BLEND:开启混合
        SetGLEnabled(GL_BLEND, true);
        //设置混合函数
        RenderCommandBuffer::SetBlendFuncHandler(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //上传mvp矩阵
        SetUniformMatrix4fv(shaderProgramHandle, "u_model", false, model);
        SetUniformMatrix4fv(shaderProgramHandle, "u_view", false, camera->GetView());
        SetUniformMatrix4fv(shaderProgramHandle, "u_projection", false, camera->GetProjection());
        SetUniformMatrix4fv(shaderProgramHandle, "u_mvp", false, mvp);

        //拿到保存的Texture
        auto textures = material->GetTextures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            auto textureUnit = GL_TEXTURE0 + texture_index;
            auto textureHandle = textures[texture_index].second->GetTextureHandle();
            RenderCommandBuffer::ActiveAndBindTextureHandler(textureUnit, textureHandle);

            //设置Shader程序从纹理单元读取颜色数据
            auto uniformName = textures[texture_index].first.c_str();
            RenderCommandBuffer::SetUniformIntHandler(shaderProgramHandle, const_cast<char *>(uniformName),
                                                      texture_index);
        }

        //Material Render
        material->Render(shaderProgramHandle);

        RenderCommandBuffer::BindVAOAndDrawElementsHandler(vaoHandle, mesh->vertex_index_num);

        GetGameObject()->ForeachComponent([](Component *component) {
            component->OnPostprocessRender();
        });
    }

    void MeshRenderer::SetGLEnabled(unsigned int state, bool enabled) {
        RenderCommandBuffer::SetStateEnableHandler(state, enabled);
    }

    void MeshRenderer::SetUniformMatrix4fv(unsigned int shaderProgramHandle, const char *uniformName, bool transpose,
                                           glm::mat4 &matrix) {
        RenderCommandBuffer::SetUniformMatrix4fvHandler(shaderProgramHandle, uniformName, transpose, matrix);
    }

} // DivineBrush