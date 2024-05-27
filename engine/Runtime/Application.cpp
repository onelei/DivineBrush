//
// Created by onelei on 2024/3/8.
//

#include "Application.h"
#include "EditorApplication.h"

namespace DivineBrush {
    class EditorApplication;

    std::string Application::data_path;
    std::string Application::persistent_data_path;

    void Application::Init(std::string &dataPath, std::string &persistentDataPath) {
        data_path = dataPath;
        persistent_data_path = persistentDataPath;
        EditorApplication::Init();
        Run();
    }

    void Application::Run() {
        EditorApplication::Run();
    }
} // DivineBrush
