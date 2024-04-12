//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_RENDERPROGRAMGENERATER_H
#define ENGINE_RENDERPROGRAMGENERATER_H

#include <GL/glew.h>
#include <unordered_map>

namespace DivineBrush {

    class RenderProgramGenerater {
    public:
        unsigned int CreateShader() {
            return ++shaderIndex;
        }

        unsigned int CreateVAO() {
            return ++vaoIndex;
        }

        unsigned int CreateVBO() {
            return ++vboIndex;
        }

        unsigned int CreateTexture() {
            return ++textureIndex;
        }

        void SetShader(unsigned int key, GLuint value) {
            shaderMap[key] = value;
        }

        GLuint GetShader(unsigned int key) {
            return shaderMap[key];
        }

        void SetVAO(unsigned int key, GLuint value) {
            vaoMap[key] = value;
        }

        GLuint GetVAO(unsigned int key) {
            return vaoMap[key];
        }

        void SetVBO(unsigned int key, GLuint value) {
            vboMap[key] = value;
        }

        GLuint GetVBO(unsigned int key) {
            return vboMap[key];
        }

        void SetTexture(unsigned int key, GLuint value) {
            textureMap[key] = value;
        }

        GLuint GetTexture(unsigned int key) {
            return textureMap[key];
        }

    private:
        unsigned int shaderIndex;//Shader程序索引
        unsigned int vaoIndex;//VAO索引
        unsigned int vboIndex;//VBO索引
        unsigned int textureIndex;//Texture索引

        std::unordered_map<unsigned int, GLuint> shaderMap;//Shader程序映射表
        std::unordered_map<unsigned int, GLuint> vaoMap;//VAO映射表
        std::unordered_map<unsigned int, GLuint> vboMap;//VBO映射表
        std::unordered_map<unsigned int, GLuint> textureMap;//Texture映射表
    };

} // DivineBrush

#endif //ENGINE_RENDERPROGRAMGENERATER_H
