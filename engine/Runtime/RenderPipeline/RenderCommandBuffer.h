//
// Created by onelei on 2024/4/25.
//

#ifndef ENGINE_RENDERCOMMANDBUFFER_H
#define ENGINE_RENDERCOMMANDBUFFER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <rigtorp/SPSCQueue.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include "Handler/RenderCommandHandler.h"
#include "../Render/MeshFilter.h"

namespace DivineBrush {

    class RenderCommandBuffer {
    public :
        static void Enqueue(RenderCommandHandler *handler);

        static void CreateCompressedTexImage2DHandler(unsigned int textureHandle,
                                                      int width,
                                                      int height,
                                                      unsigned int textureFormat,
                                                      int compressSize,
                                                      unsigned char *data);

        static void DeleteTexturesHandler(unsigned int *textureHandleArray, int textureCount);

        static void CreateTexImage2DHandler(unsigned int textureHandle,
                                            int width,
                                            int height,
                                            unsigned int internalformat,
                                            unsigned int format,
                                            unsigned int dataType,
                                            unsigned char *data, unsigned int dataSize);

        static void UpdateScreenSizeHandler(GLFWwindow *window);

        static void EndFrameHandler(GLFWwindow *window);

        static void CompileShaderHandler(char *vertexShaderSource,
                                         char *fragmentShaderSource,
                                         unsigned int shaderProgramHandle);

        static void UseShaderProgramHandler(unsigned int shaderProgramHandle);

        static void CreateVAOHandler(unsigned int shaderProgramHandle,
                                     unsigned int vaoHandle,
                                     unsigned int vboHandle,
                                     unsigned int vertexDataSize,
                                     void *vertexData,
                                     unsigned short vertexIndexDataSize,
                                     void * vertexIndexData);

        static void UpdateVBODataHandler(unsigned int vboHandle,
                                         unsigned int vertexDataSize,
                                         void *vertexData);

        static void UpdateUBODataHandler(std::string name,
                                         std::string memberName,
                                         void *data);

        static void SetStateEnableHandler(unsigned int state, bool enabled);

        static void SetBlendFuncHandler(unsigned int sFactor, unsigned int dFactor);

        static void
        SetUniformMatrix4fvHandler(unsigned int shader_program_handle, const char *uniformName, bool transpose,
                                   glm::mat4 &matrix);

        static void ActiveAndBindTextureHandler(unsigned int textureUnit, unsigned int textureHandle);

        static void SetUniformIntHandler(unsigned int shaderProgramHandle, const char *uniformName, int value);

        static void SetUniformFloatHandler(unsigned int shaderProgramHandle, const char *uniformName, float value);

        static void
        SetUniformVector3Handler(unsigned int shaderProgramHandle, const char *uniformName, glm::vec3 value);

        static void BindVAOAndDrawElementsHandler(unsigned int vaoHandle, unsigned int vertexIndexCount);

        static void SetStencilBufferClearValueHandler(int clearValue);

        static void SetStencilFuncHandler(unsigned int func, int ref, unsigned int mask);

        static void SetStencilOpHandler(unsigned int fail,
                                        unsigned int zFail,
                                        unsigned int zPass);

        static void SetClearFlagAndClearColorBufferHandler(unsigned int clearFlag,
                                                           float clearColorR,
                                                           float clearColorG,
                                                           float clearColorB,
                                                           float clearColorA);

        static void UpdateTextureSubImage2DHandler(unsigned int textureHandle,
                                                   int x,
                                                   int y,
                                                   int width,
                                                   int height,
                                                   unsigned int format,
                                                   unsigned int type,
                                                   unsigned char *data,
                                                   unsigned int dataSize);

        static void BindUniformBufferHandler(unsigned int shaderProgramHandle);

        static void CreateUBOHandler(unsigned int shaderProgramHandle,
                                     unsigned int uboHandle,
                                     char *name,
                                     unsigned int size,
                                     void *data);

        static void BindMeshHandler(std::vector<MeshFilter::Vertex> vertices, std::vector<unsigned short> indices);

        static bool IsEmpty();

        static RenderCommandHandler *Peek();

        static void Dequeue();

        static size_t GetCount();

    private:
        static rigtorp::SPSCQueue<RenderCommandHandler *> ringBuffer;
    };

} // DivineBrush

#endif //ENGINE_RENDERCOMMANDBUFFER_H
