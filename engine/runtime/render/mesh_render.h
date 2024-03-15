//
// Created by onelei on 2024/3/15.
//

#ifndef ENGINE_MESH_RENDER_H
#define ENGINE_MESH_RENDER_H

#include <string>
#include <glm/detail/type_mat4x4.hpp>
#include "material.h"
#include "mesh_filter.h"

namespace DivineBrush {

    class MeshRender {
    public:
        MeshRender() = default;

        ~MeshRender() = default;

        void SetMaterial(Material *material) { this->material = material; }

        Material *GetMaterial() { return material; }

        void SetMeshFilter(MeshFilter *meshFilter) { this->mesh_filter = meshFilter; }

        MeshFilter *GetMeshFilter() { return mesh_filter; }

        void SetMVP(glm::mat4 mvp) { this->mvp = mvp; }

        glm::mat4 GetMVP() { return mvp; }

        void Prepare();
        void Render();

    private:
        Material *material = nullptr;
        MeshFilter *mesh_filter = nullptr;
        unsigned int program_id;
        glm::mat4 mvp;
        GLint mvp_location, vpos_location, vcol_location, a_uv_location;
        GLuint kVBO, kEBO;
        GLuint kVAO;
    };

} // DivineBrush

#endif //ENGINE_MESH_RENDER_H
