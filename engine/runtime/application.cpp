//
// Created by onelei on 2024/3/8.
//

#include "application.h"
#include "render/render.h"

namespace DivineBrush {

    void Application::Init() {
        this->render = new class Render();
        render->Init();
        Run();
    }

    void Application::Update() {

    }

    void Application::Render() {

    }

    void Application::UpdateScreenSize() {

    }

    void Application::Run() {
        this->render->Run();
    }
} // DivineBrush
