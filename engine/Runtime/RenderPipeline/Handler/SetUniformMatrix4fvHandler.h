//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETUNIFORMMATRIX4FVHANDLER_H
#define ENGINE_SETUNIFORMMATRIX4FVHANDLER_H

#include <glm/mat4x4.hpp>
#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class SetUniformMatrix4fvHandler : public RenderCommandHandler {
    public:
        SetUniformMatrix4fvHandler() {
            renderCommand = RenderCommand::SetUniformMatrix4fv;
        }

        ~SetUniformMatrix4fvHandler() {
            free(uniformName);
        }

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        bool transpose = false;
        glm::mat4 *matrix = nullptr;
    };


} // DivineBrush

#endif //ENGINE_SETUNIFORMMATRIX4FVHANDLER_H
