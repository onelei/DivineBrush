//
// Created by onelei on 2024/6/14.
//

#ifndef ENGINE_BINDMESHHANDLER_H
#define ENGINE_BINDMESHHANDLER_H

#include <vector>
#include <GL/glew.h>
#include "RenderCommandHandler.h"
#include "../../Render/MeshFilter.h"

namespace DivineBrush {

    class BindMeshHandler : public RenderCommandHandler {
    public:
        BindMeshHandler();

        ~BindMeshHandler();

        GLuint VAO, VBO, EBO;
        std::vector<MeshFilter::Vertex> vertices;
        std::vector<unsigned int> indices;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_BINDMESHHANDLER_H
