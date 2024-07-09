//
// Created by onelei on 2024/3/13.
//

#include <fstream>
#include <filesystem>
#include <codecvt>
#include "rttr/registration.h"
#include "MeshFilter.h"
#include "../Application.h"
#include "../../depends/debug/debug.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
#include "MeshRenderer.h"
#include "../Component/GameObject.h"

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
        boneInfo = (BoneInfo *)(malloc(fileSize - 6));
        fileStream.read((char *) boneInfo, fileSize - 6);
        fileStream.close();
    }

    void MeshFilter::LoadMesh(const std::string &filePath) {
        std::ifstream input_file_stream(Application::GetDataPath()+filePath,std::ios::in | std::ios::binary);
        MeshFileHead meshFileHead;
        input_file_stream.read((char*)&meshFileHead, sizeof(meshFileHead));
        //读取顶点数据
        auto vertex_data =(char*)malloc(meshFileHead.vertex_num * sizeof(Vertex));
        input_file_stream.read((char*)vertex_data, meshFileHead.vertex_num * sizeof(Vertex));
        //读取顶点索引数据
        auto vertex_index_data = (unsigned short *) malloc(meshFileHead.vertex_index_num * sizeof(unsigned short));
        input_file_stream.read((char *) vertex_index_data, meshFileHead.vertex_index_num * sizeof(unsigned short));
        input_file_stream.close();

        mesh = new Mesh();
        mesh->name = meshFileHead.name;
        mesh->vertex_num = meshFileHead.vertex_num;
        mesh->vertex_index_num = meshFileHead.vertex_index_num;
        mesh->vertex_data = (Vertex *) vertex_data;
        mesh->vertex_index_data = vertex_index_data;
    }

    void MeshFilter::ExportMesh(const std::string &filePath) {
        auto fullPath = Application::GetDataPath() + filePath;
        if (!std::filesystem::exists(fullPath)){
            Debug::LogError("Texture2D::LoadFile Texture file not found: " + fullPath);
            return;
        }

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(fullPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        std::vector<MeshFile*> meshFiles;
        ProcessNode(scene->mRootNode, scene,meshFiles);

        for (auto meshFile:meshFiles) {
            auto meshName = meshFile->meshFileHead.name;
            std::filesystem::path inputPath(fullPath);
            std::string inputFileName = inputPath.filename().stem().string();
            std::string outputFileName=fmt::format("{}_{}.mesh", inputFileName, meshName);
            inputPath.replace_filename(outputFileName);
            auto filename = inputPath.string();

            std::ofstream outputFile(filename, std::ios::binary);
            if (!outputFile.is_open()) {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return;
            }

            outputFile.write(reinterpret_cast<const char*>(&meshFile->meshFileHead), sizeof(meshFile->meshFileHead));
            outputFile.write(reinterpret_cast<const char*>(meshFile->vertex_data), sizeof(Vertex) * meshFile->meshFileHead.vertex_num);
            outputFile.write(reinterpret_cast<const char*>(meshFile->vertex_index_data), sizeof(unsigned short) * meshFile->meshFileHead.vertex_index_num);
            outputFile.close();
        }

    }

    void MeshFilter::ProcessNode(aiNode *node, const aiScene *scene, std::vector<MeshFile *> &meshFiles) {
        // 处理节点所有的mesh
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            auto aiMesh = scene->mMeshes[node->mMeshes[i]];
            auto meshFile = ProcessMesh(aiMesh);
            meshFiles.push_back(meshFile);
        }

        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, meshFiles);
        }
    }

    MeshFilter::MeshFile* MeshFilter::ProcessMesh(const aiMesh *aiMesh) {
        auto meshFile = new MeshFile();
        meshFile->meshFileHead.vertex_num = aiMesh->mNumFaces * 3; // 每个面有3个顶点
        meshFile->vertex_data = new Vertex[meshFile->meshFileHead.vertex_num];
        meshFile->meshFileHead.vertex_index_num = aiMesh->mNumFaces * 3;
        meshFile->vertex_index_data = new unsigned short[meshFile->meshFileHead.vertex_index_num];

        unsigned int index = 0;
        for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i) {
            const aiFace& face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                unsigned int vertexIndex = face.mIndices[j];
                meshFile->vertex_index_data[index] = index;

                meshFile->vertex_data[index].pos =
                        glm::vec3(aiMesh->mVertices[vertexIndex].x, aiMesh->mVertices[vertexIndex].y,
                                  aiMesh->mVertices[vertexIndex].z);
                if (aiMesh->HasVertexColors(0)) {
                    meshFile->vertex_data[index].color = glm::vec4(aiMesh->mColors[0][vertexIndex].r, aiMesh->mColors[0][vertexIndex].g, aiMesh->mColors[0][vertexIndex].b, aiMesh->mColors[0][vertexIndex].a);
                } else {
                    meshFile->vertex_data[index].color = glm::vec4(1.0f); // 默认颜色
                }
                if (aiMesh->HasTextureCoords(0)) {
                    auto uv = aiMesh->mTextureCoords[0][vertexIndex];
                    meshFile->vertex_data[index].uv = glm::vec2(uv.x,  uv.y);
                } else {
                    meshFile->vertex_data[index].uv = glm::vec2(0.0f); // 默认UV
                }
                ++index;
            }
        }

        // 复制mesh名称

        // 获取UTF-8编码的名称
        std::string mesh_name = aiMesh->mName.C_Str();
        // 转换为UTF-16编码
        std::wstring utf16_name = utf8_to_utf16(mesh_name);
        // 截取UTF-16编码的名称到31个字符以内
        if (utf16_name.size() > 31) {
            utf16_name = utf16_name.substr(0, 31);
        }
        // 转换回UTF-8编码
        std::string truncated_name = utf16_to_utf8(utf16_name);
        // 复制到meshFileHead.name字段，确保不超过31个字符，并以空字符结尾
        std::strncpy(meshFile->meshFileHead.name, truncated_name.c_str(), 31);
        meshFile->meshFileHead.name[31] = '\0';

        std::strncpy(meshFile->meshFileHead.type, "Mesh", 4);

        return meshFile;
    }

    std::wstring MeshFilter::utf8_to_utf16(const std::string &utf8_str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(utf8_str);
    }

    std::string MeshFilter::utf16_to_utf8(const std::wstring &utf16_str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(utf16_str);
    }


} // DivineBrush