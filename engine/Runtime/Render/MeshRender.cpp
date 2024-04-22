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
#include "../RenderPipeline/Handler/UpdateVBOSubDataHandler.h"
#include "../RenderPipeline/Handler/SetStateEnableHandler.h"
#include "../RenderPipeline/Handler/SetBlendFuncHandler.h"
#include "../RenderPipeline/Handler/SetUniformMatrix4fvHandler.h"
#include "../RenderPipeline/Handler/ActiveAndBindTextureHandler.h"
#include "../RenderPipeline/Handler/SetUniform1iHandler.h"
#include "../RenderPipeline/Handler/BindVAOAndDrawElementsHandler.h"
#include "../RenderPipeline/RenderGenerater.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<MeshRender>("MeshRender")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    void MeshRender::Prepare() {
        //获取Shader中的变量
        auto shader = material->GetShader();
        shaderProgramHandle = shader->GetProgramHandle();
        auto component_mesh_filter = gameObject->GetComponent("MeshFilter");
        mesh_filter = dynamic_cast<MeshFilter *>(component_mesh_filter);
        if (!mesh_filter) {
            return;
        }
        vaoHandle = RenderGenerater::CreateVAO();
        vboHandle = RenderGenerater::CreateVBO();
        auto handler = ObjectPool<CreateVAOHandler>::Get();
        auto mesh = mesh_filter->GetMesh();
        handler->vaoHandle = vaoHandle;
        handler->vboHandle = vboHandle;
        auto vertexDataSize = mesh->vertex_num * sizeof(MeshFilter::Vertex);
        handler->vertexDataSize = vertexDataSize;
        handler->vertexTypeSize = sizeof(MeshFilter::Vertex);

        handler->vertexData= (unsigned char*)malloc(vertexDataSize);
        memcpy(handler->vertexData, mesh->vertex_data, vertexDataSize);

        auto vertexIndexDataSize = mesh->vertex_index_num * sizeof(unsigned short);
        handler->vertexIndexDataSize = vertexIndexDataSize;
        handler->vertexIndexData= (unsigned char*)malloc(vertexIndexDataSize);
        memcpy(handler->vertexIndexData, mesh->vertex_index_data, vertexIndexDataSize);

        handler->shaderProgramHandle = shaderProgramHandle;
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
        if (camera == nullptr) {
            return;
        }

        //对两个数的位进行逐位的与(AND)操作。如果两个相应的位都为1，则该位的结果为1；否则，为0。
        if ((GetGameObject()->GetLayer() & camera->GetCullingMask()) == 0x00) {
            return;
        }
        auto mesh = mesh_filter->GetMesh();

        if (vaoHandle == 0) {
            Prepare();
        } else {
//            auto handler = ObjectPool<UpdateVBOSubDataHandler>::Get();
//            handler->vboHandle = vboHandle;
//            auto vertexDataSize = mesh->vertex_num * sizeof(MeshFilter::Vertex);
//            handler->vertexDataSize = vertexDataSize;
//            handler->vertexData= (unsigned char*)malloc(vertexDataSize);
//            memcpy(handler->vertexData, mesh->vertex_data, vertexDataSize);
//            RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
        }

        //进行实际的渲染调用：这里你绘制你的场景，包括提到的立方体渲染。
        glm::mat4 trans = glm::translate(transform->GetPosition()); //不移动顶点坐标;

        auto rotation = transform->GetRotation();
        auto eulerAngleYXZ = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x),
                                                glm::radians(rotation.z)); //使用欧拉角旋转;

        auto scale = glm::scale(transform->GetScale()); //缩放;
        auto model = trans * scale * eulerAngleYXZ;

        auto mvp = camera->GetProjection() * camera->GetView() * model;

        auto shader = material->GetShader();
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
        auto handler = ObjectPool<SetBlendFuncHandler>::Get();
        handler->sFactor = GL_SRC_ALPHA;
        handler->dFactor = GL_ONE_MINUS_SRC_ALPHA;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
        //上传mvp矩阵
        //SetUniformMatrix4fv(shaderProgramHandle, "u_model", false, model);
        //SetUniformMatrix4fv(shaderProgramHandle, "u_view", false, camera->GetView());
        //SetUniformMatrix4fv(shaderProgramHandle, "u_projection", false, camera->GetProjection());
        SetUniformMatrix4fv(shaderProgramHandle, "u_mvp", false, mvp);

        //拿到保存的Texture
        auto textures = material->GetTextures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            auto textureHandler = ObjectPool<ActiveAndBindTextureHandler>::Get();
            textureHandler->textureUnit = GL_TEXTURE0 + texture_index;
            textureHandler->textureHandle = textures[texture_index].second->GetTextureHandle();
            RenderPipeline::GetInstance().AddRenderCommandHandler(textureHandler);

            //设置Shader程序从纹理单元读取颜色数据
            auto uniformHandler = ObjectPool<SetUniform1iHandler>::Get();
            uniformHandler->shaderProgramHandle = shaderProgramHandle;
            auto uniformName = textures[texture_index].first.c_str();
            uniformHandler->uniformName = new char[strlen(uniformName) + 1];  // 加1因为需要为结尾的空字符腾出空间
            strcpy(uniformHandler->uniformName, uniformName);
            uniformHandler->value = texture_index;
            RenderPipeline::GetInstance().AddRenderCommandHandler(uniformHandler);
        }

        auto bindHandler = ObjectPool<BindVAOAndDrawElementsHandler>::Get();
        bindHandler->vaoHandle = vaoHandle;
        bindHandler->vertexIndexCount = mesh->vertex_index_num;
        RenderPipeline::GetInstance().AddRenderCommandHandler(bindHandler);

        GetGameObject()->ForeachComponent([](Component *component) {
            component->OnPostprocessRender();
        });
    }

    void MeshRender::SetGLEnabled(unsigned int state, bool enabled) {
        auto handler = ObjectPool<SetStateEnableHandler>::Get();
        handler->enable = enabled;
        handler->state = state;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
    }

    void MeshRender::SetUniformMatrix4fv(unsigned int shader_program_handle, const char *uniformName, bool transpose,
                                         glm::mat4 &matrix) {
        auto handler = ObjectPool<SetUniformMatrix4fvHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uniformName= static_cast<char *>(malloc(strlen(uniformName) + 1));
        strcpy(handler->uniformName, uniformName);
        handler->transpose = transpose;
        handler->matrix = matrix;
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);
    }

} // DivineBrush