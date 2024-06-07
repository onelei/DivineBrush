#include <iostream>
#include "Texture2d.h"

int main(int argc, char **argv) {
//    glfwSetErrorCallback(error_callback);
//
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    glfwMakeContextCurrent(window);
//    gladLoadGL(glfwGetProcAddress);
//    glfwSwapInterval(1);
//
    std::cout << "Hello, World!" << std::endl;
    for (int i = 1; i < argc; ++i) {
        std::string src(argv[i]);
        std::string dst = src;
        auto last_index_of_point = dst.find_last_of('.');
        dst.replace(last_index_of_point, dst.size() - last_index_of_point, ".glt");
        DivineBrush::Texture2d::CompressFile(src, dst);
    }
    return 0;
}
