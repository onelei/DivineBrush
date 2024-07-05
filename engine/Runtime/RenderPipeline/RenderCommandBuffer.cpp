//
// Created by onelei on 2024/4/25.
//

#include "RenderCommandBuffer.h"
#include "../../depends/template/ObjectPool.h"
#include "Handler/CreateCompressedTexImage2DHandler.h"
#include "Handler/DeleteTexturesHandler.h"
#include "Handler/CreateTexImage2DHandler.h"
#include "RenderGenerater.h"
#include "Handler/UpdateScreenSizeHandler.h"
#include "Handler/EndFrameHandler.h"
#include "Handler/CompileShaderHandler.h"
#include "Handler/UseShaderProgramHandler.h"
#include "Handler/SetStateEnableHandler.h"
#include "Handler/SetUniformMatrix4fvHandler.h"
#include "Handler/CreateVAOHandler.h"
#include "Handler/SetBlendFuncHandler.h"
#include "Handler/ActiveAndBindTextureHandler.h"
#include "Handler/SetUniformIntHandler.h"
#include "Handler/SetUniformFloatHandler.h"
#include "Handler/SetUniformVector3Handler.h"
#include "Handler/BindVAOAndDrawElementsHandler.h"
#include "Handler/SetStencilBufferClearValueHandler.h"
#include "Handler/SetStencilFuncHandler.h"
#include "Handler/SetStencilOpHandler.h"
#include "Handler/SetClearFlagAndClearColorBufferHandler.h"
#include "Handler/UpdateTextureSubImage2DHandler.h"
#include "Handler/UpdateVBODataHandler.h"
#include "Handler/UpdateUBODataHandler.h"
#include "Handler/BindUniformBufferHandler.h"
#include "Handler/CreateUBOHandler.h"
#include "Handler/BindMeshHandler.h"

namespace DivineBrush {
    rigtorp::SPSCQueue<RenderCommandHandler *> RenderCommandBuffer::ringBuffer = rigtorp::SPSCQueue<RenderCommandHandler *>(
            1024);

    void RenderCommandBuffer::Enqueue(RenderCommandHandler *handler) {
        ringBuffer.push(handler);
    }

    bool RenderCommandBuffer::IsEmpty() {
        return ringBuffer.empty();
    }

    RenderCommandHandler *RenderCommandBuffer::Peek() {
        return *(ringBuffer.front());
    }

    void RenderCommandBuffer::Dequeue() {
        ringBuffer.pop();
    }

    size_t RenderCommandBuffer::GetCount() {
        return ringBuffer.size();
    }

    void RenderCommandBuffer::CreateCompressedTexImage2DHandler(unsigned int textureHandle,
                                                                int width,
                                                                int height,
                                                                unsigned int textureFormat,
                                                                int compressSize,
                                                                unsigned char *data) {
        auto handler = ObjectPool<DivineBrush::CreateCompressedTexImage2DHandler>::Get();//ObjectPool<DivineBrush::CreateCompressedTexImage2DHandler>::Get();
        handler->textureHandle = textureHandle;
        handler->width = width;
        handler->height = height;
        handler->textureFormat = textureFormat;
        handler->compressSize = compressSize;
        handler->data = static_cast<unsigned char *>(malloc(compressSize));
        memcpy(handler->data, data, compressSize);
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::DeleteTexturesHandler(unsigned int *textureHandleArray, int textureCount) {
        auto handler = ObjectPool<DivineBrush::DeleteTexturesHandler>::Get();
        handler->textureCount = textureCount;
        auto size = sizeof(unsigned int) * handler->textureCount;
        handler->textureHandleArray = (unsigned int *) malloc(size);
        memcpy(handler->textureHandleArray, &textureHandleArray, size);
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::CreateTexImage2DHandler(unsigned int textureHandle,
                                                      int width,
                                                      int height,
                                                      unsigned int internalformat,
                                                      unsigned int format,
                                                      unsigned int dataType,
                                                      unsigned char *data, unsigned int dataSize) {
        auto handler = ObjectPool<DivineBrush::CreateTexImage2DHandler>::Get();
        handler->textureHandle = textureHandle;
        handler->width = width;
        handler->height = height;
        handler->internalformat = internalformat;
        handler->format = format;
        handler->dataType = dataType;
        handler->data = static_cast<unsigned char *>(malloc(dataSize));
        memcpy(handler->data, data, dataSize);
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::UpdateScreenSizeHandler(GLFWwindow *window) {
        auto handler = ObjectPool<DivineBrush::UpdateScreenSizeHandler>::Get();
        handler->window = window;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::EndFrameHandler(GLFWwindow *window) {
        auto handler = ObjectPool<DivineBrush::EndFrameHandler>::Get();
        handler->window = window;
        RenderCommandBuffer::Enqueue(handler);
        ///等待渲染结束任务，说明渲染线程渲染完了这一帧所有的东西。
        handler->Wait();
        handler->Clear();
    }

    void RenderCommandBuffer::CompileShaderHandler(char *vertexShaderSource,
                                                   char *fragmentShaderSource,
                                                   unsigned int shaderProgramHandle) {
        auto handler = ObjectPool<DivineBrush::CompileShaderHandler>::Get();
        handler->vertexShaderSource = static_cast<char *>(malloc(strlen(vertexShaderSource) + 1));
        strcpy(handler->vertexShaderSource, vertexShaderSource);

        handler->fragmentShaderSource = static_cast<char *>(malloc(strlen(fragmentShaderSource) + 1));
        strcpy(handler->fragmentShaderSource, fragmentShaderSource);

        handler->shaderProgramHandle = shaderProgramHandle;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::UseShaderProgramHandler(unsigned int shaderProgramHandle) {
        auto handler = ObjectPool<DivineBrush::UseShaderProgramHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::CreateVAOHandler(unsigned int shaderProgramHandle,
                                               unsigned int vaoHandle,
                                               unsigned int vboHandle,
                                               unsigned int vertexDataSize,
                                               void *vertexData,
                                               unsigned short vertexIndexDataSize,
                                               void *vertexIndexData) {
        auto handler = ObjectPool<DivineBrush::CreateVAOHandler>::Get();
        handler->vaoHandle = vaoHandle;
        handler->vboHandle = vboHandle;
        handler->vertexDataSize = vertexDataSize;
        handler->vertexData = (unsigned char *) malloc(vertexDataSize);
        memcpy(handler->vertexData, vertexData, vertexDataSize);
        handler->vertexIndexDataSize = vertexIndexDataSize;
        handler->vertexIndexData = (unsigned char *) malloc(vertexIndexDataSize);
        memcpy(handler->vertexIndexData, vertexIndexData, vertexIndexDataSize);
        handler->shaderProgramHandle = shaderProgramHandle;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::UpdateVBODataHandler(unsigned int vboHandle,
                                                   unsigned int vertexDataSize,
                                                   void *vertexData) {
        auto handler = ObjectPool<DivineBrush::UpdateVBODataHandler>::Get();
        handler->vboHandle = vboHandle;
        handler->vertexDataSize = vertexDataSize;
        handler->vertexData = (unsigned char *) malloc(vertexDataSize);
        memcpy(handler->vertexData, vertexData, vertexDataSize);
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::UpdateUBODataHandler(std::string name,
                                                   std::string memberName,
                                                   void *data) {
        auto handler = ObjectPool<DivineBrush::UpdateUBODataHandler>::Get();
        handler->name = name;
        handler->memberName = memberName;
        handler->data = data;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetStateEnableHandler(unsigned int state, bool enabled) {
        auto handler = ObjectPool<DivineBrush::SetStateEnableHandler>::Get();
        handler->enable = enabled;
        handler->state = state;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetBlendFuncHandler(unsigned int sFactor, unsigned int dFactor) {
        //设置混合函数
        auto handler = ObjectPool<DivineBrush::SetBlendFuncHandler>::Get();
        handler->sFactor = sFactor;
        handler->dFactor = dFactor;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetUniformMatrix4fvHandler(unsigned int shaderProgramHandle, const char *uniformName,
                                                         bool transpose,
                                                         glm::mat4 &matrix) {
        auto handler = ObjectPool<DivineBrush::SetUniformMatrix4fvHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uniformName = static_cast<char *>(malloc(strlen(uniformName) + 1));
        strcpy(handler->uniformName, uniformName);
        handler->transpose = transpose;
        handler->matrix = matrix;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::ActiveAndBindTextureHandler(unsigned int textureUnit, unsigned int textureHandle) {
        auto handler = ObjectPool<DivineBrush::ActiveAndBindTextureHandler>::Get();
        handler->textureUnit = textureUnit;
        handler->textureHandle = textureHandle;
        RenderCommandBuffer::Enqueue(handler);
    }

    void
    RenderCommandBuffer::SetUniformIntHandler(unsigned int shaderProgramHandle, const char *uniformName, int value) {
        //设置Shader程序从纹理单元读取颜色数据
        auto handler = ObjectPool<DivineBrush::SetUniformIntHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uniformName = new char[strlen(uniformName) + 1];  // 加1因为需要为结尾的空字符腾出空间
        strcpy(handler->uniformName, uniformName);
        handler->value = value;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetUniformFloatHandler(unsigned int shaderProgramHandle, const char *uniformName,
                                                     float value) {
        //设置Shader程序从纹理单元读取颜色数据
        auto handler = ObjectPool<DivineBrush::SetUniformFloatHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uniformName = new char[strlen(uniformName) + 1];  // 加1因为需要为结尾的空字符腾出空间
        strcpy(handler->uniformName, uniformName);
        handler->value = value;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetUniformVector3Handler(unsigned int shaderProgramHandle, const char *uniformName,
                                                       glm::vec3 value) {
        //设置Shader程序从纹理单元读取颜色数据
        auto handler = ObjectPool<DivineBrush::SetUniformVector3Handler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uniformName = new char[strlen(uniformName) + 1];  // 加1因为需要为结尾的空字符腾出空间
        strcpy(handler->uniformName, uniformName);
        handler->value = value;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::BindVAOAndDrawElementsHandler(unsigned int vaoHandle, unsigned int vertexIndexCount) {
        auto handler = ObjectPool<DivineBrush::BindVAOAndDrawElementsHandler>::Get();
        handler->vaoHandle = vaoHandle;
        handler->vertexIndexCount = vertexIndexCount;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetStencilBufferClearValueHandler(int clearValue) {
        auto handler = ObjectPool<DivineBrush::SetStencilBufferClearValueHandler>::Get();
        handler->clearValue = clearValue;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetStencilFuncHandler(unsigned int func, int ref, unsigned int mask) {
        auto handler = ObjectPool<DivineBrush::SetStencilFuncHandler>::Get();
        handler->func = func;
        handler->ref = ref;
        handler->mask = mask;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetStencilOpHandler(unsigned int fail,
                                                  unsigned int zFail,
                                                  unsigned int zPass) {
        auto handler = ObjectPool<DivineBrush::SetStencilOpHandler>::Get();
        handler->fail = fail;
        handler->zFail = zFail;
        handler->zPass = zPass;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::SetClearFlagAndClearColorBufferHandler(unsigned int clearFlag,
                                                                     float clearColorR,
                                                                     float clearColorG,
                                                                     float clearColorB,
                                                                     float clearColorA) {
        auto handler = ObjectPool<DivineBrush::SetClearFlagAndClearColorBufferHandler>::Get();
        handler->clearFlag = clearFlag;
        handler->clearColorR = clearColorR;
        handler->clearColorG = clearColorG;
        handler->clearColorB = clearColorB;
        handler->clearColorA = clearColorA;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::UpdateTextureSubImage2DHandler(unsigned int textureHandle,
                                                             int x,
                                                             int y,
                                                             int width,
                                                             int height,
                                                             unsigned int format,
                                                             unsigned int type,
                                                             unsigned char *data,
                                                             unsigned int dataSize) {
        auto handler = ObjectPool<DivineBrush::UpdateTextureSubImage2DHandler>::Get();
        handler->textureHandle = textureHandle;
        handler->x = x;
        handler->y = y;
        handler->width = width;
        handler->height = height;
        handler->format = format;
        handler->type = type;
        handler->data = (unsigned char *) malloc(dataSize);
        memcpy(handler->data, data, dataSize);
        handler->dataSize = dataSize;
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::BindUniformBufferHandler(unsigned int shaderProgramHandle) {
        auto handler = ObjectPool<DivineBrush::BindUniformBufferHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        RenderCommandBuffer::Enqueue(handler);
    }

    void
    RenderCommandBuffer::CreateUBOHandler(unsigned int shaderProgramHandle, unsigned int uboHandle, char *name,
                                          unsigned int size,
                                          void *data) {
        auto handler = ObjectPool<DivineBrush::CreateUBOHandler>::Get();
        handler->shaderProgramHandle = shaderProgramHandle;
        handler->uboHandle = uboHandle;
        handler->name = name;
        handler->size = size;
        handler->data = (unsigned char *) malloc(size);
        memcpy(handler->data, data, size);
        RenderCommandBuffer::Enqueue(handler);
    }

    void RenderCommandBuffer::BindMeshHandler(std::vector<MeshFilter::Vertex> vertices, std::vector<unsigned short> indices) {
        auto handler = ObjectPool<DivineBrush::BindMeshHandler>::Get();
        handler->vertices = std::move(vertices);
        handler->indices = std::move(indices);
        RenderCommandBuffer::Enqueue(handler);
    }


} // DivineBrush