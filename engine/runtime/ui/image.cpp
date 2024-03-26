//
// Created by onelei on 2024/2/29.
//

#include <iostream>
#include "image.h"
#include "../render/mesh_filter.h"
#include "../object/game_object.h"
#include "rttr/registration.h"
#include "../render/render_control.h"

namespace DivineBrush::UI {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Image>("Image")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Image::Image() {

    }

    Image::~Image() {

    }

    void Image::Load(std::string filename) {
        texture2d = Texture2d::LoadCompressFile(filename);
    }

    void Image::OnUpdate() {
        if (texture2d == nullptr) {
            return;
        }
        auto mesh_filter = dynamic_cast<MeshFilter *>(GetGameObject()->GetComponent("MeshFilter"));
        if (mesh_filter != nullptr) {
            return;
        }
        Component::OnUpdate();
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
        mesh_filter = dynamic_cast<MeshFilter *>(GetGameObject()->AddComponent("MeshFilter"));
        mesh_filter->CreateMesh(vertex_vector, index_vector);
        //创建 Material
        auto material = new Material();//设置材质
        material->Parse("material/image.mat");
        //使用图片贴图
        material->SetTexture("u_diffuse_texture", texture2d);

        //挂上 MeshRender 组件
        auto pMeshRender = dynamic_cast<MeshRender *>(GetGameObject()->AddComponent("MeshRender"));
        pMeshRender->SetMaterial(material);
        pMeshRender->SetMeshFilter(mesh_filter);
    }

    void Image::OnPreprocessRender() {
        Component::OnPreprocessRender();
        glStencilFunc(GL_EQUAL, 0x1, 0xFF);//等于1 通过测试 ,就是上次绘制的图 的范围 才通过测试。
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//没有通过测试的，保留原来的，也就是保留上一次的值。
    }

    void Image::OnPostprocessRender() {
        Component::OnPostprocessRender();
        RenderControl::Disable(RenderControl::RenderState::StencilTest);
    }

} // DivineBrush