cmake_minimum_required(VERSION 3.26)
project(engine)

set(CMAKE_CXX_STANDARD 17)

#more warning
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (WIN32)
    #ignore warning unicode
    add_compile_options(/wd4819)
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(rttr CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(spdlog CONFIG REQUIRED)

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
        editor/window/project/project_window.h
        runtime/ui/ui_behaviour.cpp
        runtime/ui/ui_behaviour.h
        depends/template/array_pool.h
        depends/template/dynamic_array_pool.h
        depends/template/dynamic_array_pool.h
        runtime/ui/texture.cpp
        runtime/ui/texture.h
        runtime/ui/texture2d.cpp
        runtime/ui/texture2d.h
        runtime/render/render.cpp
        runtime/render/render.h
        runtime/application.cpp
        runtime/application.h
        runtime/render/shader.cpp
        runtime/render/shader.h
        depends/time/stop_watch.h
        runtime/render/mesh_filter.cpp
        runtime/render/mesh_filter.h
        runtime/render/material.cpp
        runtime/render/material.h
        runtime/render/mesh_render.cpp
        runtime/render/mesh_render.h
        runtime/render/camera.cpp
        runtime/render/camera.h
        runtime/input/input.cpp
        runtime/input/input.h
        runtime/screen/screen.cpp
        runtime/screen/screen.h
        samples/scene/sample_scene.cpp
        samples/scene/sample_scene.h
        runtime/object/scene.cpp
        runtime/object/scene.h
        depends/debug/debug.cpp
        depends/debug/debug.h
        runtime/ui/font.cpp
        runtime/ui/font.h
        depends/vector/vector2f.h
        depends/vector/vector3f.h
        depends/vector/vector4f.h
        runtime/render/render_control.cpp
        runtime/render/render_control.h
        runtime/render/render_control.cpp
        runtime/ui/mask.cpp
        runtime/ui/mask.h
        runtime/ui/mask.h
        depends/node/node.cpp
        depends/node/node.h
        runtime/ui/text.cpp
        runtime/ui/text.h)

find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")

include_directories(${PROJECT_SOURCE_DIR}/depends/imgui/backends
        ${RAPIDXML_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        main.cpp
        resources/app_icon.rc
        ${SOURCE_FILES}
        ${IMGUI_BACKENDS}
        runtime/object/object.cpp
        runtime/object/object.h
        runtime/object/object.h
        runtime/ui/image.cpp
        runtime/ui/image.h
        runtime/ui/image.h
        runtime/object/transform.cpp
        runtime/object/transform.h
        runtime/object/component.cpp
        runtime/object/component.h
        runtime/object/game_object.cpp
        runtime/object/game_object.h
        runtime/object/game_object.h)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad::glad
        opengl32
        glm::glm
        RTTR::Core
        imgui::imgui
        freeimage::FreeImage freeimage::FreeImagePlus
        GLEW::GLEW
        Freetype::Freetype
        spdlog::spdlog)