//
// Created by onelei on 2024/4/11.
//

#include "RenderGenerater.h"

namespace DivineBrush {
    unsigned int RenderGenerater::shaderIndex;//Shader程序索引
    unsigned int RenderGenerater::vaoIndex;//VAO索引
    unsigned int RenderGenerater::vboIndex;//VBO索引
    unsigned int RenderGenerater::uboIndex;//UBO索引
    unsigned int RenderGenerater::textureIndex;//Texture索引

    std::unordered_map<unsigned int, GLuint> RenderGenerater::shaderMap;//Shader程序映射表
    std::unordered_map<unsigned int, GLuint> RenderGenerater::vaoMap;//VAO映射表
    std::unordered_map<unsigned int, GLuint> RenderGenerater::vboMap;//VBO映射表
    std::unordered_map<unsigned int, GLuint> RenderGenerater::uboMap;//UBO映射表
    std::unordered_map<unsigned int, GLuint> RenderGenerater::textureMap;//Texture映射表
    unsigned int RenderGenerater::CreateShader() {
        return ++shaderIndex;
    }

    unsigned int RenderGenerater::CreateVAO() {
        return ++vaoIndex;
    }

    unsigned int RenderGenerater::CreateVBO() {
        return ++vboIndex;
    }

    unsigned int RenderGenerater::CreateTexture() {
        return ++textureIndex;
    }

    void RenderGenerater::SetShader(unsigned int key, GLuint value) {
        shaderMap[key] = value;
    }

    GLuint RenderGenerater::GetShader(unsigned int key) {
        return shaderMap[key];
    }

    void RenderGenerater::SetVAO(unsigned int key, GLuint value) {
        vaoMap[key] = value;
    }

    GLuint RenderGenerater::GetVAO(unsigned int key) {
        return vaoMap[key];
    }

    void RenderGenerater::SetVBO(unsigned int key, GLuint value) {
        vboMap[key] = value;
    }

    GLuint RenderGenerater::GetVBO(unsigned int key) {
        return vboMap[key];
    }

    void RenderGenerater::SetTexture(unsigned int key, GLuint value) {
        textureMap[key] = value;
    }

    GLuint RenderGenerater::GetTexture(unsigned int key) {
        return textureMap[key];
    }

    unsigned int RenderGenerater::CreateUBO() {
        return ++uboIndex;
    }

    void RenderGenerater::SetUBO(unsigned int key, GLuint value) {
        uboMap[key] = value;
    }

    GLuint RenderGenerater::GetUBO(unsigned int key) {
        return uboMap[key];
    }

} // DivineBrush