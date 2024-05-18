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
        UseShaderProgram,
        CreateVAO,
        UpdateVBOData,
        UpdateUBOData,
        CreateCompressedTexImage2D,
        CreateTexImage2D,
        DeleteTextures,
        UpdateTextureSubImage2D,
        SetStateEnable,
        SetBlendFunc,
        SetUniformMatrix4fv,
        ActiveAndBindTexture,
        SetUniform1i,
        BindVAOAndDrawElements,
        SetClearFlagAndClearColorBuffer,
        SetStencilFunc,
        SetStencilOp,
        SetStencilBufferClearValue,
        EndFrame,
    };
} // DivineBrush

#endif //ENGINE_RENDERCOMMAND_H
