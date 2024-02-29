cmake_minimum_required(VERSION 3.26)
project(hello)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(hello main.cpp)

target_link_libraries(hello PRIVATE glfw glad::glad opengl32)

