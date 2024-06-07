//
// Created by onelei on 2024/5/23.
//

#include "SkinnedMeshRenderer.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"
#include "../Animation/Animation.h"

namespace DivineBrush {
    RTTR_REGISTRATION {
        rttr::registration::class_<SkinnedMeshRenderer>("SkinnedMeshRenderer")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    SkinnedMeshRenderer::SkinnedMeshRenderer() {

    }

    SkinnedMeshRenderer::~SkinnedMeshRenderer() {

    }

    void SkinnedMeshRenderer::OnUpdate() {
        auto meshFilter = GetGameObject()->GetComponent<MeshFilter>();
        if (meshFilter == nullptr) {
            return;
        }
        auto mesh = meshFilter->GetMesh();
        if (mesh == nullptr) {
            return;
        }
        auto boneInfo = meshFilter->GetBoneInfo();
        if (boneInfo == nullptr) {
            return;
        }
        auto animation = GetGameObject()->GetComponent<Animation>();
        if (animation == nullptr) {
            return;
        }
        auto animationClip = animation->GetAnimationClip();
        auto boneMat4 = animationClip->GetCurrentFrameBoneMat4();
        auto boneMat3 = animationClip->GetCurrentFrameNormalBoneMat3();
        auto skinMesh = meshFilter->GetSkinMesh();
        if (skinMesh == nullptr) {
            auto meshSize = mesh->GetSize();
            skinMesh = static_cast<MeshFilter::Mesh *>(malloc(meshSize));
            memcpy(skinMesh, mesh, meshSize);
            meshFilter->SetSkinMesh(skinMesh);
            auto vertex_data_size = sizeof(MeshFilter::Vertex) * mesh->vertex_num;
            skinMesh->vertex_data = static_cast<MeshFilter::Vertex *>(malloc(vertex_data_size));
            memcpy(skinMesh->vertex_data, mesh->vertex_data, vertex_data_size);
        }
        //计算当前帧的骨骼矩阵
        for (int i = 0; i < skinMesh->vertex_num; i++) {
            auto vertex = mesh->vertex_data[i];
            auto vertexPos = glm::vec4(vertex.pos, 1.0f);
            glm::vec4 bonePos;
            glm::vec3 boneNormal;
            for (int j = 0; j < 4; j++) {
                auto boneIndex = boneInfo[i].index[j];
                if (boneIndex == -1)
                    continue;
                auto boneWeight = boneInfo[i].weight[j] / 100.0f;
                bonePos = bonePos + boneMat4[boneIndex] * vertexPos * boneWeight;
                //TODO SkinMesh
                //boneNormal = boneNormal + boneMat3[boneIndex] * vertex.normal * boneWeight;
            }
            skinMesh->vertex_data[i].pos = glm::vec3(bonePos);
            //TODO SkinMesh
            //skinMesh->vertex_data[i].normal = boneNormal;
        }
    }

    void SkinnedMeshRenderer::Render() {
        MeshRenderer::Render();
    }
} // DivineBrush