//
// Created by onelei on 2024/5/23.
//

#include "SkinnedMeshRenderer.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"

namespace DivineBrush {
    RTTR_REGISTRATION
    {
        rttr::registration::class_<SkinnedMeshRenderer>("SkinnedMeshRenderer")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }
    SkinnedMeshRenderer::SkinnedMeshRenderer() {

    }

    SkinnedMeshRenderer::~SkinnedMeshRenderer() {

    }

    void SkinnedMeshRenderer::OnUpdate() {
        Component::OnUpdate();
        auto meshFilter = GetGameObject()->GetComponent<MeshFilter>();
        if(meshFilter== nullptr){
            return;
        }
        auto mesh = meshFilter->GetMesh();
        if(mesh== nullptr){
            return;
        }
    }

    void SkinnedMeshRenderer::Render() {
        MeshRenderer::Render();
    }
} // DivineBrush