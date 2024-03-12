//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include "../ui/texture/texture2d.h"

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

        GLuint GetColorTextureId(){
            return color_texture_id_;
        }

    private:
        GLFWwindow *window;
        Texture2d *texture2d;
        GLuint color_texture_id_=0;//FBO 颜色纹理
        GLuint depth_texture_id_=0;//FBO 深度纹理
    };

} // DivineBrush

#endif //ENGINE_RENDER_H
