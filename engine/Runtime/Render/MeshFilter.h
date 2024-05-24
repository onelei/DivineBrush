//
// Created by onelei on 2024/3/13.
//

#ifndef ENGINE_MESHFILTER_H
#define ENGINE_MESHFILTER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "fstream"
#include "../Component/Component.h"

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
            glm::vec3 normal;
        };

        struct MeshFileHead {
            char type[4];
            char name[32];
            unsigned short vertex_num;
            unsigned short vertex_index_num;
        };

        struct Mesh {
            char *name = nullptr;
            unsigned short vertex_num = 0;
            unsigned short vertex_index_num = 0;
            Vertex *vertex_data = nullptr;
            unsigned short *vertex_index_data = nullptr;

            ~Mesh() {
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

        struct BoneInfo {
            //骨骼顶点索引
            char index[4];
            //骨骼权重
            char weight[4];
        };

        void LoadMesh(const std::string& filePath);

        void CreateMesh(std::vector<Vertex> &vertex_data, std::vector<unsigned short> &vertex_index_data);

        void CreateMeshLua(std::vector<float> &vertex_data, std::vector<unsigned short> &vertex_index_data);

        Mesh *GetMesh() {
            return this->mesh;
        }

        Mesh *GetSkinMesh() {
            return this->skinMesh;
        }

        void SetSkinMesh(Mesh *mesh) {
            this->skinMesh = mesh;
        }

        const char *GetMeshName(){
            return this->mesh->name;
        }

        BoneInfo *GetBoneInfo() {
            return this->boneInfo;
        }

        void SetBoneInfo(std::vector<int> &boneInfoData);

        void LoadWeight(std::string filePath);

    private:
        Mesh *mesh = nullptr;
        Mesh *skinMesh = nullptr;
        BoneInfo *boneInfo = nullptr;
    };

} // DivineBrush

#endif //ENGINE_MESHFILTER_H
