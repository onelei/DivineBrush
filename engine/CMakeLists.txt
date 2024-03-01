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
        ${PROJECT_SOURCE_DIR}/depends/imgui/backends/imgui_impl_opengl3.cpp
        editor/window/editor_window.h
        editor/window/hierarchy/hierarchy_editor_window.cpp
        editor/window/hierarchy/hierarchy_editor_window.h
        editor/window/editor_window.cpp)

include_directories(${PROJECT_SOURCE_DIR}/depends/imgui/backends)

add_executable(${PROJECT_NAME} main.cpp
        ${IMGUI_BACKENDS}
        runtime/component/object.cpp
        runtime/component/object.h
        runtime/component/object.h
        runtime/ui/ui_image.cpp
        runtime/ui/ui_image.h
        runtime/ui/ui_image.h
        runtime/component/transform.cpp
        runtime/component/transform.h
        runtime/component/component.cpp
        runtime/component/component.h
        runtime/component/game_object.cpp
        runtime/component/game_object.h
        runtime/component/game_object.h)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad::glad opengl32 glm::glm RTTR::Core imgui::imgui)