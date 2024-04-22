//
// Created by onelei on 2024/3/8.
//

#include "Application.h"
#include "Render/Render.h"

namespace DivineBrush {
    std::string Application::data_path;
    std::string Application::persistent_data_path;
    Render *render;

    void Application::Init(std::string &dataPath, std::string &persistentDataPath) {
        data_path = dataPath;
        persistent_data_path = persistentDataPath;
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
