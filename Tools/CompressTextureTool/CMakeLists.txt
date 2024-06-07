cmake_minimum_required(VERSION 3.26)
project(CompressTextureTool)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/bigobj)
    add_compile_options(/wd4819)#忽略保存为unicode警告
    add_compile_options(/utf-8)  # 设置 MSVC 编译器使用 UTF-8 编码
endif ()

find_package(Stb REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${Stb_INCLUDE_DIR})

add_executable(CompressTextureTool main.cpp
        Texture2d.h
        Texture2d.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)