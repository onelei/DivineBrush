//
// Created by onelei on 2024/3/13.
//

#include <fstream>
#include "MeshFilter.h"
#include "../application.h"
#include "rttr/registration.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<MeshFilter>("MeshFilter")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }
    MeshFilter::MeshFilter():mesh(nullptr) {

    }

    MeshFilter::~MeshFilter() {
        if (mesh != nullptr) {
            delete mesh;
        }
    }

    void MeshFilter::LoadMesh(const char *mesh_file_path) {
        //读取 Mesh文件头
        std::ifstream input_file_stream(Application::GetDataPath()+mesh_file_path, std::ios::in | std::ios::binary);
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

    void ExportMesh(char* mesh_file_path) {
//        std::ofstream output_file_stream(Application::GetDataPath()+mesh_file_path, std::ios::out | std::ios::binary);
//        MeshFilter::MeshFileHead mesh_file_head;
//        mesh_file_head.type[0] = 'm';
//        mesh_file_head.type[1] = 'e';
//        mesh_file_head.type[2] = 's';
//        mesh_file_head.type[3] = 'h';
//        mesh_file_head.vertex_num = kVertexRemoveDumplicateVector.size();
//        mesh_file_head.vertex_index_num = kVertexIndexVector.size();
//        output_file_stream.write((char *) &mesh_file_head, sizeof(mesh_file_head));
//        output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0], kVertexRemoveDumplicateVector.size() * sizeof(Vertex));
//        output_file_stream.write((char *)&kVertexIndexVector[0], kVertexIndexVector.size() * sizeof(unsigned short));
//        output_file_stream.close();
    }

    void MeshFilter::CreateMesh(std::vector<Vertex> &vertex_data, std::vector<unsigned short> &vertex_index_data) {
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
} // DivineBrush