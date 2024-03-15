//
// Created by onelei on 2024/3/13.
//

#ifndef ENGINE_MESH_FILTER_H
#define ENGINE_MESH_FILTER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "fstream"

namespace DivineBrush {

    class MeshFilter {
    public:
        MeshFilter();

        ~MeshFilter();

    public:
        struct Vertex {
            glm::vec3 pos;
            glm::vec4 color;
            glm::vec2 uv;
        };

        struct MeshFileHead {
            char type[4];
            unsigned short vertex_num;
            unsigned short vertex_index_num;
        };

        struct Mesh {
            unsigned short vertex_num;
            unsigned short vertex_index_num;
            Vertex *vertex_data;
            unsigned short *vertex_index_data;
        };

        void LoadMesh(const char *mesh_file_path);



        Mesh *GetMesh() {
            return this->mesh;
        }

    private:
        Mesh *mesh = nullptr;
    };
//原始顶点数组
    static const MeshFilter::Vertex kVertexs[36] ={
            //Front
            glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3( 1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

            //back
            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

            //left
            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

            //right
            glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

            //up
            glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

            //down
            glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

            glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
    };

//去重的顶点Vector
    static std::vector<MeshFilter::Vertex> kVertexRemoveDumplicateVector;
//顶点索引Vector
    static std::vector<unsigned short> kVertexIndexVector;

//顶点去重
    static void VertexRemoveDumplicate(char* mesh_file_path) {
        for (int i = 0; i < 36; ++i) {
            const MeshFilter::Vertex &vertex = kVertexs[i];
            //判断顶点是否存在
            int index = -1;
            for (int j = 0; j < kVertexRemoveDumplicateVector.size(); ++j) {
                if (vertex.pos == kVertexRemoveDumplicateVector[j].pos &&
                    vertex.color == kVertexRemoveDumplicateVector[j].color &&
                    vertex.uv == kVertexRemoveDumplicateVector[j].uv) {
                    index = j;
                    break;
                }
            }
            if (index < 0) {
                //没找到就将目标顶点加入kVertexRemoveDumplicateVector，并记录索引为kVertexRemoveDumplicateVector.size()。
                kVertexRemoveDumplicateVector.push_back(vertex);
                kVertexIndexVector.push_back(kVertexRemoveDumplicateVector.size() - 1);
            } else {
                //找到了目标顶点，记录索引为kVertexRemoveDumplicateVector的位置。
                kVertexIndexVector.push_back(index);
            }
        }

        std::ofstream output_file_stream(mesh_file_path, std::ios::out | std::ios::binary);
        MeshFilter::MeshFileHead mesh_file_head;
        mesh_file_head.type[0] = 'm';
        mesh_file_head.type[1] = 'e';
        mesh_file_head.type[2] = 's';
        mesh_file_head.type[3] = 'h';
        mesh_file_head.vertex_num = kVertexRemoveDumplicateVector.size();
        mesh_file_head.vertex_index_num = kVertexIndexVector.size();
        output_file_stream.write((char *) &mesh_file_head, sizeof(mesh_file_head));
        output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0], kVertexRemoveDumplicateVector.size() * sizeof(MeshFilter::Vertex));
        output_file_stream.write((char *)&kVertexIndexVector[0], kVertexIndexVector.size() * sizeof(unsigned short));
        output_file_stream.close();
    }
    static void ExportMesh(char* mesh_file_path);
} // DivineBrush

#endif //ENGINE_MESH_FILTER_H
