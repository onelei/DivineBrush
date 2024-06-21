#include "runtime/Application.h"

// Main code
int main(int, char **) {
    //Log("log start2");
    std::string dataPath = "../samples/";
    std::string persistentDataPath;
    DivineBrush::Application::Init(dataPath, persistentDataPath);
    return 0;
}