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
        editor/window/hierarchy/hierarchy_window.cpp
        editor/window/hierarchy/hierarchy_window.h
        editor/window/editor_window.cpp
        runtime/serialization/scriptable_object.cpp
        runtime/serialization/scriptable_object.h
        editor/window/inspector/inspector_window.cpp
        editor/window/inspector/inspector_window.h
        editor/window/inspector/inspector_window.h
        editor/window/scene/scene_window.cpp
        editor/window/scene/scene_window.h
        editor/window/scene/scene_window.h
        editor/window/console/console_window.cpp
        editor/window/console/console_window.h
        editor/window/console/console_window.h
        editor/window/game/game_window.cpp
        editor/window/game/game_window.h
        editor/window/project/project_window.cpp
        editor/window/project/project_window.h)

include_directories(${PROJECT_SOURCE_DIR}/depends/imgui/backends)

add_executable(${PROJECT_NAME} main.cpp
        ${IMGUI_BACKENDS}
        runtime/object/object.cpp
        runtime/object/object.h
        runtime/object/object.h
        runtime/ui/ui_image.cpp
        runtime/ui/ui_image.h
        runtime/ui/ui_image.h
        runtime/object/transform.cpp
        runtime/object/transform.h
        runtime/object/component.cpp
        runtime/object/component.h
        runtime/object/game_object.cpp
        runtime/object/game_object.h
        runtime/object/game_object.h)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad::glad opengl32 glm::glm RTTR::Core imgui::imgui)