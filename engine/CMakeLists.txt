cmake_minimum_required(VERSION 3.26)
project(engine)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    #ignore warning unicode
    add_compile_options(/wd4819)
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(rttr CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(IMGUI_BACKENDS
        ${PROJECT_SOURCE_DIR}/depends/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/depends/imgui/backends/imgui_impl_opengl3.cpp)

include_directories(${PROJECT_SOURCE_DIR}/depends/imgui/backends)

add_executable(${PROJECT_NAME} main.cpp
        ${IMGUI_BACKENDS}
        core/object.cpp
        core/object.h
        core/object.h
        ui/ui_image.cpp
        ui/ui_image.h
        ui/ui_image.h
        core/transform.cpp
        core/transform.h
        core/component.cpp
        core/component.h
        core/game_object.cpp
        core/game_object.h
        core/game_object.h)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad::glad opengl32 glm::glm RTTR::Core imgui::imgui)