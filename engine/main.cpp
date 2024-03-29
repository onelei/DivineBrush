// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp


#include "runtime/application.h"
#include "depends/debug/debug.h"

// Main code
int main(int, char **) {
    DivineBrush::Debug::Init();
    //Log("log start2");
    std::string dataPath = "../samples/";
    std::string persistentDataPath;
    DivineBrush::Application::Init(dataPath, persistentDataPath);
    return 0;
}
