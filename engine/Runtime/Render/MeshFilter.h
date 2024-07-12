//
// Created by onelei on 2024/3/13.
//

#ifndef ENGINE_MESHFILTER_H
#define ENGINE_MESHFILTER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include "fstream"
#include "../Component/Component.h"
#include "Material.h"

namespace DivineBrush {

    class MeshFilter : public Component {
    public:
        MeshFilter();

        ~MeshFilter();

    public:
        struct Vertex {
            glm::vec3 pos;
            glm::vec4 color;
            glm::vec2 uv;
            //TODO SkinMesh
            //glm::vec3 normal;
        };

        struct MeshFileHead {
            char type[4];
            char name[32];
            unsigned short vertex_num;
            unsigned short vertex_index_num;
        };

        struct MeshFile {
            MeshFileHead meshFileHead;
            Vertex *vertex_data = nullptr;
            unsigned short *vertex_index_data = nullptr;

            ~MeshFile() {
                if (vertex_data) {
                    delete[] vertex_data;
                    vertex_data = nullptr;
                }
                if (vertex_index_data) {
                    delete[] vertex_index_data;
                    vertex_index_data = nullptr;
                }
            }
        };

        struct Mesh {
            char *name = nullptr;
            unsigned short vertex_num = 0;
            unsigned short vertex_index_num = 0;
            Vertex *vertex_data = nullptr;
            unsigned short *vertex_index_data = nullptr;

            ~Mesh() {
                if (name) {
                    delete[] name;
                    name = nullptr;
                }
                if (vertex_data) {
                    delete[] vertex_data;
                    vertex_data = nullptr;
                }
                if (vertex_index_data) {
                    delete[] vertex_index_data;
                    vertex_index_data = nullptr;
                }
            }

            unsigned short GetSize() {
                return sizeof(vertex_num) + sizeof(Vertex) * vertex_num
                       + sizeof(vertex_index_num) + vertex_index_num * sizeof(unsigned short);
            }
        };

        // 顶点关联骨骼及权重,每个顶点最多可以关联4个骨骼。
        struct BoneInfo {
            //骨骼顶点索引
            char index[4];//骨骼索引，一般骨骼少于128个，用char就行。
            //骨骼权重
            char weight[4];//骨骼权重，权重不会超过100，所以用char类型就可以。
        };

        struct WeightFile {
            BoneInfo* boneInfo = nullptr;
            int vertexCount;

            WeightFile(int vertexCount){
                boneInfo = new BoneInfo[vertexCount];
                this->vertexCount = vertexCount;
            }

            ~WeightFile() {
                if (boneInfo) {
                    delete[] boneInfo;
                    boneInfo = nullptr;
                }
            }
        };

        void LoadMesh(const std::string &filePath);

        void CreateMesh(std::vector<Vertex> &vertex_data, std::vector<unsigned short> &vertex_index_data);

        void CreateMeshLua(std::vector<float> &vertex_data, std::vector<unsigned short> &vertex_index_data);

        Mesh *GetMesh() {
            return this->mesh;
        }

        Mesh *GetSkinMesh() {
            return this->skinMesh;
        }

        void SetSkinMesh(Mesh *skinMesh) {
            this->skinMesh = skinMesh;
        }

        const char *GetMeshName() {
            return this->mesh->name;
        }

        BoneInfo *GetBoneInfo() {
            return this->boneInfo;
        }

        void SetBoneInfo(std::vector<int> &boneInfoData);

        void LoadWeight(std::string filePath);

        static void ExportMesh(const std::string &filePath);

        static void ProcessNode(aiNode *node, const aiScene *scene, std::vector<MeshFile *> &meshFiles);

        static MeshFile *ProcessMesh(const aiMesh *aiMesh);

        static void ExportWeight(const std::string& filePath);

    private:
        Mesh *mesh = nullptr;
        Mesh *skinMesh = nullptr;
        BoneInfo *boneInfo = nullptr;

        std::string fullPath;
    RTTR_ENABLE(Component);
    };

} // DivineBrush

#endif //ENGINE_MESHFILTER_H
