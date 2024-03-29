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
        Editor/Window/EditorWindow.h
        Editor/Window/HierarchyWindow.cpp
        Editor/Window/HierarchyWindow.h
        Editor/Window/EditorWindow.cpp
        Runtime/Serialize/ScriptableObject.cpp
        Runtime/Serialize/ScriptableObject.h
        Editor/Window/InspectorWindow.cpp
        Editor/Window/InspectorWindow.h
        Editor/Window/InspectorWindow.h
        Editor/Window/SceneWindow.cpp
        Editor/Window/SceneWindow.h
        Editor/Window/SceneWindow.h
        Editor/Window/ConsoleWindow.cpp
        Editor/Window/ConsoleWindow.h
        Editor/Window/ConsoleWindow.h
        Editor/Window/GameWindow.cpp
        Editor/Window/GameWindow.h
        Editor/Window/project_window.cpp
        Editor/Window/project_window.h
        Runtime/UI/UIBehaviour.cpp
        Runtime/UI/UIBehaviour.h
        depends/template/array_pool.h
        depends/template/dynamic_array_pool.h
        depends/template/dynamic_array_pool.h
        Runtime/UI/Texture.cpp
        Runtime/UI/Texture.h
        Runtime/UI/Texture2d.cpp
        Runtime/UI/Texture2d.h
        Runtime/Render/Render.cpp
        Runtime/Render/Render.h
        Runtime/application.cpp
        Runtime/application.h
        Runtime/Render/Shader.cpp
        Runtime/Render/Shader.h
        depends/time/stop_watch.h
        Runtime/Render/MeshFilter.cpp
        Runtime/Render/MeshFilter.h
        Runtime/Render/Material.cpp
        Runtime/Render/Material.h
        Runtime/Render/MeshRender.cpp
        Runtime/Render/MeshRender.h
        Runtime/Render/Camera.cpp
        Runtime/Render/Camera.h
        Runtime/Input/Input.cpp
        Runtime/Input/Input.h
        Runtime/Screen/Screen.cpp
        Runtime/Screen/Screen.h
        samples/scene/sample_scene.cpp
        samples/scene/sample_scene.h
        Runtime/Component/Scene.cpp
        Runtime/Component/Scene.h
        depends/debug/debug.cpp
        depends/debug/debug.h
        Runtime/UI/Font.cpp
        Runtime/UI/Font.h
        depends/vector/vector2f.h
        depends/vector/vector3f.h
        depends/vector/vector4f.h
        Runtime/Render/RenderControl.cpp
        Runtime/Render/RenderControl.h
        Runtime/Render/RenderControl.cpp
        Runtime/UI/Mask.cpp
        Runtime/UI/Mask.h
        Runtime/UI/Mask.h
        depends/node/node.cpp
        depends/node/node.h
        Runtime/UI/Text.cpp
        Runtime/UI/Text.h
        Runtime/UI/Button.cpp
        Runtime/UI/Button.h
        depends/vector/rect_int.h
        Editor/Selection.cpp
        Editor/Selection.h)

find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")

include_directories(${PROJECT_SOURCE_DIR}/depends/imgui/backends
        ${RAPIDXML_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        Main.cpp
        Resources/app_icon.rc
        ${SOURCE_FILES}
        ${IMGUI_BACKENDS}
        Runtime/Component/Object.cpp
        Runtime/Component/Object.h
        Runtime/Component/Object.h
        Runtime/UI/Image.cpp
        Runtime/UI/Image.h
        Runtime/UI/Image.h
        Runtime/Component/Transform.cpp
        Runtime/Component/Transform.h
        Runtime/Component/Component.cpp
        Runtime/Component/Component.h
        Runtime/Component/GameObject.cpp
        Runtime/Component/GameObject.h
        Runtime/Component/GameObject.h)

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