//
// Created by onelei on 2024/3/22.
//

#include "Mask.h"
#include "rttr/registration.h"
#include "../Render/MeshFilter.h"
#include "../Component/GameObject.h"
#include "../RenderPipeline/RenderCommandBuffer.h"

namespace DivineBrush::UI {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Mask>("Mask").constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Mask::Mask() {

    }

    Mask::~Mask() {

    }

    void Mask::Load(std::string filename) {
        texture2d = Texture2d::LoadCompressFile(filename);
    }

    void Mask::OnUpdate() {
        if (texture2d == nullptr) {
            return;
        }
        Component::OnUpdate();
        auto mesh_filter = dynamic_cast<MeshFilter *>(gameObject->GetComponent("MeshFilter"));
        if (mesh_filter != nullptr) {
            return;
        }
        //创建 MeshFilter
        //生成顶点数据
        std::vector<MeshFilter::Vertex> vertex_vector = {
                {{0.f,                   0.0f,                   0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.f, 0.f}},
                {{texture2d->GetWidth(), 0.0f,                   0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.f, 0.f}},
                {{texture2d->GetWidth(), texture2d->GetHeight(), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.f, 1.f}},
                {{0.f,                   texture2d->GetHeight(), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.f, 1.f}}
        };
        std::vector<unsigned short> index_vector = {
                0, 1, 2,
                0, 2, 3
        };
        //挂上 MeshFilter 组件
        mesh_filter = dynamic_cast<MeshFilter *>(GetGameObject()->AddComponentByName("MeshFilter"));
        mesh_filter->CreateMesh(vertex_vector, index_vector);
        //创建 Material
        auto material = new Material();//设置材质
        material->Parse("material/mask.mat");
        //使用图片贴图
        material->SetTexture("u_diffuse_texture", texture2d);

        //挂上 MeshRender 组件
        auto pMeshRender = dynamic_cast<MeshRender *>(GetGameObject()->AddComponentByName("MeshRender"));
        pMeshRender->SetMaterial(material);
        pMeshRender->SetMeshFilter(mesh_filter);
    }

    void Mask::OnPreprocessRender() {
        Component::OnPreprocessRender();
        ///开启模版测试
        RenderCommandBuffer::SetStateEnableHandler(GL_STENCIL_TEST, true);
        ///设置默认模版值 0
        RenderCommandBuffer::SetStencilBufferClearValueHandler(0);
        ///通通不通过模版测试。
        RenderCommandBuffer::SetStencilFuncHandler(GL_NEVER, 0x0, 0xFF);
        ///设置模版值为0+1 = 1
        RenderCommandBuffer::SetStencilOpHandler(GL_INCR, GL_INCR, GL_INCR);
    }

    void Mask::OnPostprocessRender() {
        Component::OnPostprocessRender();
    }

    void Mask::OnEnable() {
        Component::OnEnable();
    }

    void Mask::OnDisable() {
        Component::OnDisable();
        ///关闭模版测试
        RenderCommandBuffer::SetStateEnableHandler(GL_STENCIL_TEST, false);
    }
} // DivineBrush