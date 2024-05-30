cmake_minimum_required(VERSION 3.26)
project(engine)

set(CMAKE_CXX_STANDARD 17)

#more warning
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (MSVC)
    add_compile_options(/bigobj)
    add_compile_options(/wd4819)#忽略保存为unicode警告
    add_compile_options(/utf-8)  # 设置 MSVC 编译器使用 UTF-8 编码
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(rttr CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(spdlog CONFIG REQUIRED)
list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/depends/easy_profiler/lib/cmake/easy_profiler)
find_package(easy_profiler CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(SPSCQueue CONFIG REQUIRED)
find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")

include_directories(${RAPIDXML_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/depends/easy_profiler/include
        ${LUA_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
        Main.cpp
        Resources/app_icon.rc
        ${SOURCE_FILES}
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
        Editor/Window/ProjectWindow.cpp
        Editor/Window/ProjectWindow.h
        Runtime/UI/UIBehaviour.cpp
        Runtime/UI/UIBehaviour.h
        depends/template/ArrayPool.h
        depends/template/DynamicArrayPool.h
        depends/template/DynamicArrayPool.h
        Runtime/UI/Texture.cpp
        Runtime/UI/Texture.h
        Runtime/UI/Texture2d.cpp
        Runtime/UI/Texture2d.h
        Runtime/EditorApplication.cpp
        Runtime/EditorApplication.h
        Runtime/Application.cpp
        Runtime/Application.h
        Runtime/Render/Shader.cpp
        Runtime/Render/Shader.h
        depends/time/stop_watch.h
        Runtime/Render/MeshFilter.cpp
        Runtime/Render/MeshFilter.h
        Runtime/Render/Material.cpp
        Runtime/Render/Material.h
        Runtime/Render/MeshRenderer.cpp
        Runtime/Render/MeshRenderer.h
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
        Runtime/Vector/Vector2.h
        Runtime/Vector/Vector3.h
        Runtime/Vector/Vector4.h
        Runtime/Render/RenderControl.cpp
        Runtime/Render/RenderControl.h
        Runtime/Render/RenderControl.cpp
        Runtime/UI/Mask.cpp
        Runtime/UI/Mask.h
        Runtime/UI/Mask.h
        depends/node/Node.cpp
        depends/node/Node.h
        Runtime/UI/Text.cpp
        Runtime/UI/Text.h
        Runtime/UI/Button.cpp
        Runtime/UI/Button.h
        Runtime/Vector/RectInt.h
        Editor/Selection.cpp
        Editor/Selection.h
        Runtime/Audio/Audio.cpp
        Runtime/Audio/Audio.h
        Runtime/Binder/LuaBinder.cpp
        Runtime/Binder/LuaBinder.h
        Runtime/RenderPipeline/RenderCommand.h
        Runtime/RenderPipeline/RenderPipeline.cpp
        Runtime/RenderPipeline/RenderPipeline.h
        Runtime/RenderPipeline/Handler/AsyncRenderCommandHandler.cpp
        Runtime/RenderPipeline/Handler/AsyncRenderCommandHandler.h
        Runtime/RenderPipeline/Handler/RenderCommandHandler.cpp
        Runtime/RenderPipeline/Handler/RenderCommandHandler.h
        Runtime/RenderPipeline/Handler/UpdateScreenSizeHandler.cpp
        Runtime/RenderPipeline/Handler/UpdateScreenSizeHandler.h
        Runtime/RenderPipeline/Handler/CompileShaderHandler.cpp
        Runtime/RenderPipeline/Handler/CompileShaderHandler.h
        Runtime/RenderPipeline/Handler/UseShaderProgramHandler.cpp
        Runtime/RenderPipeline/Handler/UseShaderProgramHandler.h
        Runtime/RenderPipeline/Handler/CreateCompressedTexImage2DHandler.cpp
        Runtime/RenderPipeline/Handler/CreateCompressedTexImage2DHandler.h
        Runtime/RenderPipeline/Handler/CreateTexImage2DHandler.cpp
        Runtime/RenderPipeline/Handler/CreateTexImage2DHandler.h
        Runtime/RenderPipeline/Handler/DeleteTexturesHandler.cpp
        Runtime/RenderPipeline/Handler/DeleteTexturesHandler.h
        Runtime/RenderPipeline/Handler/UpdateTextureSubImage2DHandler.cpp
        Runtime/RenderPipeline/Handler/UpdateTextureSubImage2DHandler.h
        Runtime/RenderPipeline/Handler/CreateVAOHandler.cpp
        Runtime/RenderPipeline/Handler/CreateVAOHandler.h
        Runtime/RenderPipeline/Handler/UpdateVBODataHandler.cpp
        Runtime/RenderPipeline/Handler/UpdateVBODataHandler.h
        Runtime/RenderPipeline/Handler/SetStateEnableHandler.cpp
        Runtime/RenderPipeline/Handler/SetStateEnableHandler.h
        Runtime/RenderPipeline/Handler/SetBlendFuncHandler.cpp
        Runtime/RenderPipeline/Handler/SetBlendFuncHandler.h
        Runtime/RenderPipeline/Handler/SetUniformMatrix4fvHandler.cpp
        Runtime/RenderPipeline/Handler/SetUniformMatrix4fvHandler.h
        Runtime/RenderPipeline/Handler/ActiveAndBindTextureHandler.cpp
        Runtime/RenderPipeline/Handler/ActiveAndBindTextureHandler.h
        Runtime/RenderPipeline/Handler/SetUniformIntHandler.cpp
        Runtime/RenderPipeline/Handler/SetUniformIntHandler.h
        Runtime/RenderPipeline/Handler/BindVAOAndDrawElementsHandler.cpp
        Runtime/RenderPipeline/Handler/BindVAOAndDrawElementsHandler.h
        Runtime/RenderPipeline/Handler/SetClearFlagAndClearColorBufferHandler.cpp
        Runtime/RenderPipeline/Handler/SetClearFlagAndClearColorBufferHandler.h
        Runtime/RenderPipeline/Handler/SetStencilFuncHandler.cpp
        Runtime/RenderPipeline/Handler/SetStencilFuncHandler.h
        Runtime/RenderPipeline/Handler/SetStencilOpHandler.cpp
        Runtime/RenderPipeline/Handler/SetStencilOpHandler.h
        Runtime/RenderPipeline/Handler/SetStencilBufferClearValueHandler.cpp
        Runtime/RenderPipeline/Handler/SetStencilBufferClearValueHandler.h
        Runtime/RenderPipeline/Handler/EndFrameHandler.cpp
        Runtime/RenderPipeline/Handler/EndFrameHandler.h
        depends/template/RingBuffer.h
        Runtime/RenderPipeline/RenderGenerater.cpp
        Runtime/RenderPipeline/RenderGenerater.h
        depends/template/Singleton.h
        depends/template/ObjectPool.h
        depends/template/SharedPTRObjectPool.cpp
        depends/template/SharedPTRObjectPool.h
        Runtime/RenderPipeline/Handler/CompileShaderHandler.cpp
        Runtime/RenderPipeline/Handler/CompileShaderHandler.cpp
        Runtime/RenderPipeline/Handler/CompileShaderHandler.cpp
        depends/template/Singleton.cpp
        Runtime/Physics/Collider.cpp
        Runtime/Physics/Collider.h
        Runtime/Physics/Collider.h
        Runtime/Physics/PhysicMaterial.cpp
        Runtime/Physics/PhysicMaterial.h
        Runtime/Physics/PhysicMaterial.h
        Runtime/Physics/Physics.cpp
        Runtime/Physics/Physics.h
        Runtime/Physics/SimulationEventCallback.cpp
        Runtime/Physics/SimulationEventCallback.h
        Runtime/Physics/RaycastHit.cpp
        Runtime/Physics/RaycastHit.h
        Runtime/Physics/RaycastHit.h
        Runtime/Physics/RaycastHit.h
        Runtime/Physics/RigidBody.cpp
        Runtime/Physics/RigidBody.h
        Runtime/Physics/RigidBody.h
        Runtime/Physics/BoxCollider.cpp
        Runtime/Physics/BoxCollider.h
        Runtime/Physics/BoxCollider.h
        Runtime/Physics/SphereCollider.cpp
        Runtime/Physics/SphereCollider.h
        Runtime/Physics/SphereCollider.h
        Runtime/Time/Time.cpp
        Runtime/Time/Time.h
        Runtime/Lighting/Environment.cpp
        Runtime/Lighting/Environment.h
        Runtime/Lighting/Environment.h
        Runtime/Lighting/Light.cpp
        Runtime/Lighting/Light.h
        Runtime/Lighting/Light.h
        Runtime/Render/UniformBufferManager.cpp
        Runtime/Render/UniformBufferManager.h
        Runtime/RenderPipeline/Handler/UpdateUBODataHandler.cpp
        Runtime/RenderPipeline/Handler/UpdateUBODataHandler.h
        Runtime/Animation/AnimationClip.cpp
        Runtime/Animation/AnimationClip.h
        Runtime/Animation/Animation.cpp
        Runtime/Animation/Animation.h
        Runtime/Render/SkinnedMeshRenderer.cpp
        Runtime/Render/SkinnedMeshRenderer.h
        Runtime/RenderPipeline/Handler/SetUniformFloatHandler.cpp
        Runtime/RenderPipeline/Handler/SetUniformFloatHandler.h
        Runtime/RenderPipeline/Handler/SetUniformVector3Handler.cpp
        Runtime/RenderPipeline/Handler/SetUniformVector3Handler.h
        Runtime/RenderPipeline/Handler/BindUniformBufferHandler.cpp
        Runtime/RenderPipeline/Handler/BindUniformBufferHandler.h
        Runtime/RenderPipeline/Handler/CreateUBOHandler.cpp
        Runtime/RenderPipeline/Handler/CreateUBOHandler.h
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
        Runtime/Component/GameObject.h
        Runtime/RenderPipeline/RenderCommandBuffer.cpp
        Runtime/RenderPipeline/RenderCommandBuffer.h
        Runtime/RenderPipeline/RenderCommandBuffer.h
        Runtime/Physics/RaycastHit.cpp
        Editor/Window/Layouts/DefaultLayout.cpp
        Editor/Window/Layouts/DefaultLayout.h
        Editor/Window/Layouts/BaseLayout.cpp
        Editor/Window/Layouts/BaseLayout.h)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad::glad
        opengl32
        glm::glm
        RTTR::Core
        imgui::imgui
        imguizmo::imguizmo
        d3d12
        dxgi
        freeimage::FreeImage freeimage::FreeImagePlus
        GLEW::GLEW
        Freetype::Freetype
        spdlog::spdlog
        easy_profiler
        sol2
        ${LUA_LIBRARIES}
        SPSCQueue::SPSCQueue
        unofficial::omniverse-physx-sdk::sdk
        OpenAL::OpenAL)


#if (MSVC)
#    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#else()
#    add_definitions(-D _DEBUG)
#endif ()

## Optional: import the defined target to copy over the GPU acceleration libraries (3rd party provided by NVIDIA)
#if(TARGET unofficial::omniverse-physx-sdk::gpu-library)
#    if(UNIX)
#        # Add rpath setting to find .so libraries on unix based systems
#        set_target_properties(main PROPERTIES
#                BUILD_WITH_INSTALL_RPATH TRUE
#                INSTALL_RPATH "$ORIGIN"
#        )
#    endif()
#    add_custom_command(TARGET main POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-library>
#            $<TARGET_FILE_DIR:main>)
#    if(WIN32)
#        add_custom_command(TARGET main POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-device-library>
#                $<TARGET_FILE_DIR:main>)
#    endif()
#else()
#    message(WARNING "GPU acceleration library target not defined - GPU acceleration will NOT be available!")
#endif()