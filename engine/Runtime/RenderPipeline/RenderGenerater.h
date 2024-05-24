//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_RENDERGENERATER_H
#define ENGINE_RENDERGENERATER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <unordered_map>

namespace DivineBrush {

    class RenderGenerater {

    public:
        static unsigned int CreateShader();

        static unsigned int CreateVAO();

        static unsigned int CreateVBO();

        static unsigned int CreateUBO();

        static unsigned int CreateTexture();

        static void SetShader(unsigned int key, GLuint value);

        static GLuint GetShader(unsigned int key);

        static void SetVAO(unsigned int key, GLuint value);

        static GLuint GetVAO(unsigned int key);

        static void SetVBO(unsigned int key, GLuint value);

        static GLuint GetVBO(unsigned int key);

        static void SetUBO(unsigned int key, GLuint value);

        static GLuint GetUBO(unsigned int key);

        static void SetTexture(unsigned int key, GLuint value);

        static GLuint GetTexture(unsigned int key);

    private:
        static unsigned int shaderIndex;//Shader程序索引
        static unsigned int vaoIndex;//VAO索引
        static unsigned int vboIndex;//VBO索引
        static unsigned int uboIndex;//UBO索引
        static unsigned int textureIndex;//Texture索引

        static std::unordered_map<unsigned int, GLuint> shaderMap;//Shader程序映射表
        static std::unordered_map<unsigned int, GLuint> vaoMap;//VAO映射表
        static std::unordered_map<unsigned int, GLuint> vboMap;//VBO映射表
        static std::unordered_map<unsigned int, GLuint> uboMap;//UBO映射表
        static std::unordered_map<unsigned int, GLuint> textureMap;//Texture映射表
    };

} // DivineBrush

#endif //ENGINE_RENDERGENERATER_H
