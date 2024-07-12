//
// Created by onelei on 2024/3/13.
//

#include <fstream>
#include <filesystem>
#include <codecvt>
#include <utf8h/utf8.h>
#include "utf8cpp/utf8.h"
#include "rttr/registration.h"
#include "MeshFilter.h"
#include "../Application.h"
#include "../../depends/debug/debug.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
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
        boneInfo = (BoneInfo *) (malloc(fileSize - 6));
        fileStream.read((char *) boneInfo, fileSize - 6);
        fileStream.close();
    }

    void MeshFilter::LoadMesh(const std::string &filePath) {
        std::ifstream input_file_stream(Application::GetDataPath() + filePath, std::ios::in | std::ios::binary);
        MeshFileHead meshFileHead;
        input_file_stream.read((char *) &meshFileHead, sizeof(meshFileHead));
        //读取顶点数据
        auto vertex_data = (char *) malloc(meshFileHead.vertex_num * sizeof(Vertex));
        input_file_stream.read((char *) vertex_data, meshFileHead.vertex_num * sizeof(Vertex));
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
        if (!std::filesystem::exists(fullPath)) {
            Debug::LogError("Texture2D::LoadFile Texture file not found: " + fullPath);
            return;
        }

        Assimp::Importer importer;
        // 下面两个参数不能添加
        // aiProcess_FlipUVs
        // aiProcess_JoinIdenticalVertices
        const aiScene *scene = importer.ReadFile(fullPath, aiProcess_Triangulate);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        std::vector<MeshFile *> meshFiles;
        ProcessNode(scene->mRootNode, scene, meshFiles);

        for (auto meshFile: meshFiles) {
            auto meshName = meshFile->meshFileHead.name;
            std::filesystem::path inputPath(fullPath);
            std::string inputFileName = inputPath.filename().stem().string();
            std::string outputFileName = fmt::format("{}_{}.mesh", inputFileName, meshName);
            inputPath.replace_filename(outputFileName);
            auto filename = inputPath.string();

            std::ofstream outputFile(filename, std::ios::binary);
            if (!outputFile.is_open()) {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return;
            }

            outputFile.write(reinterpret_cast<const char *>(&meshFile->meshFileHead), sizeof(meshFile->meshFileHead));
            outputFile.write(reinterpret_cast<const char *>(meshFile->vertex_data),
                             sizeof(Vertex) * meshFile->meshFileHead.vertex_num);
            outputFile.write(reinterpret_cast<const char *>(meshFile->vertex_index_data),
                             sizeof(unsigned short) * meshFile->meshFileHead.vertex_index_num);
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

    MeshFilter::MeshFile *MeshFilter::ProcessMesh(const aiMesh *aiMesh) {
        auto meshFile = new MeshFile();
        meshFile->meshFileHead.vertex_num = aiMesh->mNumVertices;
        meshFile->vertex_data = new Vertex[meshFile->meshFileHead.vertex_num];

        for (unsigned int i = 0; i < aiMesh->mNumVertices; i++) {
            meshFile->vertex_data[i].pos = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y,
                                                     aiMesh->mVertices[i].z);
            if (aiMesh->HasVertexColors(0)) {
                meshFile->vertex_data[i].color = glm::vec4(aiMesh->mColors[0][i].r, aiMesh->mColors[0][i].g,
                                                           aiMesh->mColors[0][i].b, aiMesh->mColors[0][i].a);
            } else {
                meshFile->vertex_data[i].color = glm::vec4(1.0f); // 默认颜色
            }
            if (aiMesh->HasTextureCoords(0)) {
                meshFile->vertex_data[i].uv = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
            } else {
                meshFile->vertex_data[i].uv = glm::vec2(0.0f); // 默认UV
            }
        }

        // 处理索引
        meshFile->meshFileHead.vertex_index_num = aiMesh->mNumFaces * 3;
        meshFile->vertex_index_data = new unsigned short[meshFile->meshFileHead.vertex_index_num];
        unsigned int index = 0;
        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
            const aiFace &face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                meshFile->vertex_index_data[index++] = face.mIndices[j];
            }
        }
        // 设置mesh文件头
        std::strncpy(meshFile->meshFileHead.type, "Mesh", 4);
        // 复制mesh名称
        // 将其转换为UTF-8格式
        auto meshName = aiMesh->mName.C_Str();
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        auto utf16_str = convert.from_bytes(meshName);
        std::strncpy(meshFile->meshFileHead.name, reinterpret_cast<const char *>(utf16_str.c_str()), 31); // 复制最多31个字符
        meshFile->meshFileHead.name[31] = '\0'; // 确保字符串以空字符结尾

        //TODO
        std::string _meshName = "jiulian";
        std::strcpy(meshFile->meshFileHead.name, _meshName.c_str());
        return meshFile;
    }

    void MeshFilter::ExportWeight(const std::string &filePath) {
        auto fullPath = Application::GetDataPath() + filePath;
        if (!std::filesystem::exists(fullPath)) {
            Debug::LogError("Texture2D::LoadFile Texture file not found: " + fullPath);
            return;
        }

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(fullPath, aiProcess_Triangulate);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "Error::Assimp:: " << importer.GetErrorString() << std::endl;
            return;
        }
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            aiMesh *mesh = scene->mMeshes[i];

            auto weightFile = new MeshFilter::WeightFile(mesh->mNumVertices);
            std::vector<std::vector<std::pair<int, float>>> vertexBoneData(mesh->mNumVertices);

            for (unsigned int j = 0; j < mesh->mNumBones; ++j) {
                aiBone *bone = mesh->mBones[j];
                int boneIndex = j;

                for (unsigned int k = 0; k < bone->mNumWeights; ++k) {
                    aiVertexWeight weight = bone->mWeights[k];
                    int vertexId = weight.mVertexId;
                    float weightValue = weight.mWeight;

                    vertexBoneData[vertexId].emplace_back(boneIndex, weightValue);
                }
            }

            for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
                MeshFilter::BoneInfo &boneInfo = weightFile->boneInfo[j];
                const auto &boneData = vertexBoneData[j];

                std::memset(boneInfo.index, 0, sizeof(boneInfo.index));
                std::memset(boneInfo.weight, 0, sizeof(boneInfo.weight));

                for (unsigned int k = 0; k < boneData.size() && k < 4; ++k) {
                    boneInfo.index[k] = static_cast<char>(boneData[k].first);
                    boneInfo.weight[k] = static_cast<char>(boneData[k].second * 100);
                }
            }

            std::filesystem::path inputPath(fullPath);
            inputPath.replace_extension(".weight");
            auto filename = inputPath.string();
            std::ofstream outFile(filename, std::ios::binary);
            if (!outFile) {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return;
            }

            outFile.write("weight", sizeof("weight") - 1);
            outFile.write(reinterpret_cast<char *>(weightFile->boneInfo),
                          sizeof(weightFile->boneInfo) * weightFile->vertexCount);
            outFile.close();
        }
    }

} // DivineBrush