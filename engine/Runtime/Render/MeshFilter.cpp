//
// Created by onelei on 2024/3/13.
//

#include <fstream>
#include "rttr/registration.h"
#include "MeshFilter.h"
#include "../Application.h"
#include "../../depends/debug/debug.h"
#include "../RenderPipeline/RenderCommandBuffer.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<MeshFilter>("MeshFilter")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    MeshFilter::MeshFilter() {

    }

    MeshFilter::~MeshFilter() {
        if (mesh != nullptr) {
            delete mesh;
            mesh = nullptr;
        }
        if (skinMesh != nullptr) {
            delete skinMesh;
            skinMesh = nullptr;
        }
        if (boneInfo != nullptr) {
            delete boneInfo;
            boneInfo = nullptr;
        }
    }

    void MeshFilter::CreateMesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
        this->vertices = vertices;
        this->indices = indices;
        RenderCommandBuffer::BindMeshHandler(vertices, indices);
    }

    void MeshFilter::CreateMeshLua(std::vector<float> &vertex_data, std::vector<unsigned short> &vertex_index_data) {
        if (mesh != nullptr) {
            delete mesh;
        }
        mesh = new Mesh();
        //顶点数据: 9个浮点数
        mesh->vertex_num = vertex_data.size() / 9;
        mesh->vertex_index_num = vertex_index_data.size();

        unsigned short vertex_data_size = mesh->vertex_num * sizeof(Vertex);
        mesh->vertex_data = static_cast<Vertex *>(malloc(vertex_data_size));
        memcpy(mesh->vertex_data, &vertex_data[0], vertex_data_size);

        unsigned short vertex_index_data_size = mesh->vertex_num * sizeof(unsigned short);
        mesh->vertex_index_data = static_cast<unsigned int *>(malloc(vertex_index_data_size));
        memcpy(mesh->vertex_index_data, &vertex_index_data[0], vertex_index_data_size);
    }

    void MeshFilter::SetBoneInfo(std::vector<int> &boneInfoData) {
        if (boneInfo != nullptr) {
            delete boneInfo;
        }
        auto size = boneInfoData.size() * sizeof(char);
        boneInfo = static_cast<BoneInfo *>(malloc(size));
        for (int i = 0; i < size; ++i) {
            ((char *) boneInfo)[i] = boneInfoData[i];
        }
    }

    void MeshFilter::LoadWeight(std::string filePath) {
        std::ifstream fileStream(Application::GetDataPath() + filePath, std::ios::in | std::ios::binary);
        if (!fileStream.is_open()) {
            Debug::LogError("LoadWeight: file not found " + filePath);
            return;
        }
        //读取文件头
        char fileHead[7];
        fileStream.read(fileHead, 6);
        fileHead[6] = '\0';
        if (strcmp(fileHead, "weight") != 0) {
            Debug::LogError("LoadWeight: file head error");
            return;
        }
        //读取文件权重
        fileStream.seekg(0, std::ios::end);
        int fileSize = fileStream.tellg();
        fileStream.seekg(6, std::ios::beg);
        boneInfo = static_cast<BoneInfo *>(malloc(fileSize - 6));
        fileStream.read((char *) boneInfo, fileSize - 6);
        fileStream.close();
    }

    void MeshFilter::LoadModel(const std::string &path) {
        Assimp::Importer importer;
        auto fullPath = Application::GetDataPath() + path;
        const aiScene* scene = importer.ReadFile(fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        //Mesh
        ProcessNode(scene->mRootNode, scene);

        //Material
        materials.resize(scene->mNumMaterials);
        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            materials[i].LoadFromAssimpMaterial(scene->mMaterials[i], fullPath);
        }

        RenderCommandBuffer::BindMeshHandler(vertices, indices);
    }

    void MeshFilter::ProcessNode(aiNode *node, const aiScene *scene) {
        // 处理节点中的每个网格
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
            auto mesh = ProcessMesh(aiMesh);
            meshes.push_back(mesh);
        }

        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    MeshFilter::Mesh* MeshFilter::ProcessMesh(aiMesh *aiMesh) {
        for (unsigned int i = 0; i < aiMesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.pos = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);
            vertex.normal = glm::vec3(aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z);
            vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            if (aiMesh->mTextureCoords[0]) {
                vertex.uv = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
            } else {
                vertex.uv = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
            aiFace face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        auto mesh = new MeshFilter::Mesh();
        mesh->vertex_num = vertices.size();
        mesh->vertex_index_num = indices.size();
        mesh->vertex_data = &vertices[0];
        mesh->vertex_index_data = &indices[0];
        return mesh;
    }

} // DivineBrush