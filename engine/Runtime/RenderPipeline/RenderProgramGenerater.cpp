//
// Created by onelei on 2024/4/11.
//

#include "RenderProgramGenerater.h"

namespace DivineBrush {
    unsigned int RenderProgramGenerater::CreateShader() {
        return ++shaderIndex;
    }

    unsigned int RenderProgramGenerater::CreateVAO() {
        return ++vaoIndex;
    }

    unsigned int RenderProgramGenerater::CreateVBO() {
        return ++vboIndex;
    }

    unsigned int RenderProgramGenerater::CreateTexture() {
        return ++textureIndex;
    }

    void RenderProgramGenerater::SetShader(unsigned int key, GLuint value) {
        shaderMap[key] = value;
    }

    GLuint RenderProgramGenerater::GetShader(unsigned int key) {
        return shaderMap[key];
    }

    void RenderProgramGenerater::SetVAO(unsigned int key, GLuint value) {
        vaoMap[key] = value;
    }

    GLuint RenderProgramGenerater::GetVAO(unsigned int key) {
        return vaoMap[key];
    }

    void RenderProgramGenerater::SetVBO(unsigned int key, GLuint value) {
        vboMap[key] = value;
    }

    GLuint RenderProgramGenerater::GetVBO(unsigned int key) {
        return vboMap[key];
    }

    void RenderProgramGenerater::SetTexture(unsigned int key, GLuint value) {
        textureMap[key] = value;
    }

    GLuint RenderProgramGenerater::GetTexture(unsigned int key) {
        return textureMap[key];
    }
} // DivineBrush