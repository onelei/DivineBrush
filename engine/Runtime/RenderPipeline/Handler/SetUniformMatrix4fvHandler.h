//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SETUNIFORMMATRIX4FVHANDLER_H
#define ENGINE_SETUNIFORMMATRIX4FVHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"
#include <glm/mat4x4.hpp>

namespace DivineBrush {

    class SetUniformMatrix4fvHandler : public RenderCommandHandler {
    public:
        SetUniformMatrix4fvHandler() {
            renderCommand = RenderCommand::SetUniformMatrix4fv;
        }

        ~SetUniformMatrix4fvHandler() override = default;

        unsigned int shaderProgramHandle = 0;
        char *uniformName = nullptr;
        bool transpose = false;
        glm::mat4 matrix = glm::mat4(0.0f);

        void Run() override;

        void Clear() override;
    };


} // DivineBrush

#endif //ENGINE_SETUNIFORMMATRIX4FVHANDLER_H
