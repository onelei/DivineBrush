//
// Created by onelei on 2024/3/8.
//

#include "application.h"
#include "render/render.h"

namespace DivineBrush {
    GLuint Application::color_texture_id;//FBO 颜色纹理
    GLuint Application::depth_texture_id;//FBO 深度纹理
    std::string Application::data_path;
    std::string Application::persistent_data_path;
    Render *render;

    void Application::Init(std::string &dataPath, std::string &persistentDataPath) {
        data_path = dataPath;
        persistent_data_path = persistentDataPath;
        color_texture_id = 0;//FBO 颜色纹理
        depth_texture_id = 0;//FBO 深度纹理

        render = new Render();
        render->Init();
        Run();
    }

    void Application::Update() {

    }

    void Application::UpdateScreenSize() {

    }

    void Application::Run() {
        render->Run();
    }
} // DivineBrush
