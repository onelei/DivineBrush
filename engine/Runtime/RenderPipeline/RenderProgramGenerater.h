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
        unsigned int CreateShader();

        unsigned int CreateVAO();

        unsigned int CreateVBO();

        unsigned int CreateTexture();

        void SetShader(unsigned int key, GLuint value);

        GLuint GetShader(unsigned int key);

        void SetVAO(unsigned int key, GLuint value);

        GLuint GetVAO(unsigned int key);

        void SetVBO(unsigned int key, GLuint value);

        GLuint GetVBO(unsigned int key);

        void SetTexture(unsigned int key, GLuint value);

        GLuint GetTexture(unsigned int key);

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
