//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include "../ui/texture/texture2d.h"
#include "shader.h"

namespace DivineBrush {

    class Render {
    public:
        Render() = default;

        ~Render() = default;

    public:
        int Init();

        void InitImGui();

        void Run();

        GLFWwindow *GetWindow();

        Texture2d *GetTexture2D();

        void SetTexture2D(Texture2d *texture);

        GLuint GetColorTextureId() {
            return color_texture_id;
        }

        void GeneratorVertexArrayObject();

        /// 创建VBO和EBO，设置VAO
        void GeneratorBufferObject();

    private:
        GLFWwindow *window;
        Texture2d *texture2d;
        Shader *shader;
        GLuint color_texture_id = 0;//FBO 颜色纹理
        GLuint depth_texture_id = 0;//FBO 深度纹理
    };

} // DivineBrush

#endif //ENGINE_RENDER_H
