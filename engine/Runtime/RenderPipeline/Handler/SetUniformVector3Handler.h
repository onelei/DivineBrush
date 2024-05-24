//
// Created by onelei on 2024/5/24.
//

#ifndef ENGINE_SETUNIFORMVECTOR3HANDLER_H
#define ENGINE_SETUNIFORMVECTOR3HANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"
#include "glm/glm.hpp"

namespace DivineBrush {

    class SetUniformVector3Handler : public RenderCommandHandler {
    public:
        SetUniformVector3Handler();

        ~SetUniformVector3Handler();

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        glm::vec3 value = glm::vec3(0.0f);

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_SETUNIFORMVECTOR3HANDLER_H
