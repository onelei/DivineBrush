//
// Created by onelei on 2024/5/23.
//

#include "SkinnedMeshRenderer.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"
#include "../Animation/Animation.h"
#include <glm/glm.hpp>

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
        if (!meshFilter) {
            return;
        }
        auto mesh = meshFilter->GetMesh();
        if (!mesh) {
            return;
        }
        auto boneInfo = meshFilter->GetBoneInfo();
        if (!boneInfo) {
            return;
        }
        auto animation = GetGameObject()->GetComponent<Animation>();
        if (!animation) {
            return;
        }
        auto animationClip = animation->GetAnimationClip();
        if(!animationClip){
            return;
        }
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
            auto& vertex = mesh->vertex_data[i];
            auto vertexPos = glm::vec4(vertex.pos, 1.0f);
            //对每个Bone计算一次位置，然后乘以权重，最后求和
            glm::vec4 bonePos = glm::vec4(0.0f);
            glm::vec3 boneNormal = glm::vec3(0.0f);
            for (int j = 0; j < 4; j++) {
                //顶点关联的骨骼索引
                auto boneIndex = boneInfo[i].index[j];
                if (boneIndex == -1)
                    continue;
                //顶点关联的骨骼权重
                auto boneWeight = boneInfo[i].weight[j] / 100.0f;
                //当前帧顶点关联的骨骼矩阵
                auto boneMat = boneMat4[boneIndex];
                //计算当前帧顶点位置(模型坐标系，boneMat里带了相对于模型坐标系的位置，作用到骨骼坐标系的位置上，就转换到了模型坐标系)
                auto worldPos = boneMat * vertexPos;
                bonePos = bonePos + worldPos * boneWeight;
                //TODO SkinMesh
                //boneNormal = boneNormal + boneMat3[boneIndex] * vertex.normal * boneWeight;
            }
            skinMesh->vertex_data[i].pos = glm::vec3(bonePos);
            //TODO SkinMesh
            //skinMesh->vertex_data[i].normal = boneNormal;
        }
    }
} // DivineBrush