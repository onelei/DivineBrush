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

    void MeshFilter::LoadMesh(const std::string& filePath) {
        //读取 Mesh文件头
        std::ifstream input_file_stream(Application::GetDataPath() + filePath, std::ios::in | std::ios::binary);
        MeshFileHead mesh_file_head;
        input_file_stream.read((char *) &mesh_file_head, sizeof(mesh_file_head));
        //读取顶点数据
        unsigned char *vertex_data = (unsigned char *) malloc(mesh_file_head.vertex_num * sizeof(Vertex));
        input_file_stream.read((char *) vertex_data, mesh_file_head.vertex_num * sizeof(Vertex));
        //读取顶点索引数据
        unsigned short *vertex_index_data = (unsigned short *) malloc(
                mesh_file_head.vertex_index_num * sizeof(unsigned short));
        input_file_stream.read((char *) vertex_index_data, mesh_file_head.vertex_index_num * sizeof(unsigned short));
        input_file_stream.close();

        mesh = new Mesh();
        mesh->vertex_num = mesh_file_head.vertex_num;
        mesh->vertex_index_num = mesh_file_head.vertex_index_num;
        mesh->vertex_data = (Vertex *) vertex_data;
        mesh->vertex_index_data = vertex_index_data;
    }

    void MeshFilter::CreateMesh(std::vector<Vertex> &vertex_data, std::vector<unsigned short> &vertex_index_data) {
        if (mesh != nullptr) {
            delete mesh;
        }
        mesh = new Mesh();
        mesh->vertex_num = vertex_data.size();
        mesh->vertex_index_num = vertex_index_data.size();

        unsigned short vertex_data_size = mesh->vertex_num * sizeof(Vertex);
        mesh->vertex_data = static_cast<Vertex *>(malloc(vertex_data_size));
        memcpy(mesh->vertex_data, &vertex_data[0], vertex_data_size);

        unsigned short vertex_index_data_size = mesh->vertex_num * sizeof(Vertex);
        mesh->vertex_index_data = static_cast<unsigned short *>(malloc(vertex_index_data_size));
        memcpy(mesh->vertex_index_data, &vertex_index_data[0], vertex_index_data_size);
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
        mesh->vertex_index_data = static_cast<unsigned short *>(malloc(vertex_index_data_size));
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
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        aiMesh* mesh = scene->mMeshes[0];
        //processMesh(mesh);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);

            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);

            if (mesh->mTextureCoords[0]) {
                vertices.push_back(mesh->mTextureCoords[0][i].x);
                vertices.push_back(mesh->mTextureCoords[0][i].y);
            } else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        RenderCommandBuffer::BindMeshHandler(vertices, indices);
    }

} // DivineBrush