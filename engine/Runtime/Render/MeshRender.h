//
// Created by onelei on 2024/3/15.
//

#ifndef ENGINE_MESHRENDER_H
#define ENGINE_MESHRENDER_H

#include <string>
#include <glm/detail/type_mat4x4.hpp>
#include "Material.h"
#include "MeshFilter.h"
#include "../Component/Component.h"

namespace DivineBrush {

    class MeshRender : public Component {
    public:
        MeshRender() = default;

        ~MeshRender() = default;

        void SetMaterial(Material *material) { this->material = material; }

        Material *GetMaterial() { return material; }

        void SetMeshFilter(MeshFilter *meshFilter) { this->mesh_filter = meshFilter; }

        MeshFilter *GetMeshFilter() { return mesh_filter; }

        void Render();

    private:
        Material *material = nullptr;
        MeshFilter *mesh_filter = nullptr;
        unsigned int shaderProgramHandle = 0;
        unsigned int vaoHandle = 0;
        unsigned int vboHandle = 0;

        void Prepare();

        void SetGLEnabled(unsigned int state, bool enabled);
    };

} // DivineBrush

#endif //ENGINE_MESHRENDER_H
