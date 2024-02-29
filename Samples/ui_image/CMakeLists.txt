cmake_minimum_required(VERSION 3.26)
project(ui_image)

set(CMAKE_CXX_STANDARD 17)
if (WIN32)
    #ignore warning unicode
    add_compile_options(/wd4819)
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(ui_image main.cpp)

target_link_libraries(ui_image PRIVATE glfw glad::glad GLEW::GLEW freeimage::FreeImage freeimage::FreeImagePlus)
