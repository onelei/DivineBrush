//
// Created by onelei on 2024/3/15.
//

#ifndef ENGINE_MESHRENDERER_H
#define ENGINE_MESHRENDERER_H

#include <string>
#include <glm/detail/type_mat4x4.hpp>
#include "Material.h"
#include "MeshFilter.h"
#include "../Component/Component.h"

namespace DivineBrush {

    class MeshRenderer : public Component {
    public:
        MeshRenderer() = default;

        ~MeshRenderer() = default;

        void SetMaterial(Material *material) { this->material = material; }

        Material *GetMaterial() { return material; }

        void SetMeshFilter(MeshFilter *meshFilter) { this->mesh_filter = meshFilter; }

        MeshFilter *GetMeshFilter() { return mesh_filter; }

        virtual void Render();

    private:
        Material *material = nullptr;
        MeshFilter *mesh_filter = nullptr;
        unsigned int shaderProgramHandle = 0;
        unsigned int vaoHandle = 0;
        unsigned int vboHandle = 0;

        void Prepare();

        void SetGLEnabled(unsigned int state, bool enabled);

        void SetUniformMatrix4fv(unsigned int shader_program_handle, const char *uniform_name, bool transpose,
                                 glm::mat4 &matrix);
    };

} // DivineBrush

#endif //ENGINE_MESHRENDERER_H
