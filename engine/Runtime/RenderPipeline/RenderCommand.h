//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_RENDERCOMMAND_H
#define ENGINE_RENDERCOMMAND_H

namespace DivineBrush {
    enum RenderCommand {
        None,
        UpdateScreenSize,
        CompileShader,
        BindUniformBuffer,
        UseShaderProgram,
        CreateVAO,
        UpdateVBOData,
        CreateUBO,
        UpdateUBOData,
        CreateCompressedTexImage2D,
        CreateTexImage2D,
        DeleteTextures,
        UpdateTextureSubImage2D,
        SetStateEnable,
        SetBlendFunc,
        SetUniformMatrix4fv,
        ActiveAndBindTexture,
        SetUniformInt,
        SetUniformFloat,
        SetUniformVector3,
        BindVAOAndDrawElements,
        SetClearFlagAndClearColorBuffer,
        SetStencilFunc,
        SetStencilOp,
        SetStencilBufferClearValue,
        EndFrame,
    };
} // DivineBrush

#endif //ENGINE_RENDERCOMMAND_H
