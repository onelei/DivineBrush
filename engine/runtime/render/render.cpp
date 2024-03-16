//
// Created by onelei on 2024/3/8.
//

#include "render.h"
#include <cstdio>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../../editor/window/editor_window.h"
#include "../application.h"
#include "material.h"
#include "mesh_render.h"
#include "../object/game_object.h"
#include "../object/transform.h"
#include "camera.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif


namespace DivineBrush {
    class Application;

    const char *glsl_version;

    static void glfw_error_callback(int error, const char *description) {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    int Render::Init() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            exit(EXIT_FAILURE);

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
//        OpenGL Version	GLSL Version
//        2.0	1.10
//        2.1	1.20
//        3.0	1.30
//        3.1	1.40
//        3.2	1.50
//        >3.3	=OpenGL Version

        // GL 3.0 + GLSL 130
        glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

        // Create window with graphics context
        //Dear ImGui GLFW+OpenGL3 example
        this->window = glfwCreateWindow(960, 640, "DivineBrush", nullptr, nullptr);
        if (this->window == nullptr)
            exit(EXIT_FAILURE);

        // icon
        GLFWimage image;
        DivineBrush::Texture2d::LoadGLFWimage("../resources/icon.ico", &image); // 读取图标
        glfwSetWindowIcon(this->window, 1, &image); // 设置窗口图标

        glfwMakeContextCurrent(this->window);
        glfwSwapInterval(1); // Enable vsync

        // 强制GLEW获取所有功能
        // 去掉也可
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            exit(EXIT_FAILURE);
        }


        InitImGui();

        return 0;
    }

    void Render::InitImGui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;          // Enable Docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);

        // LoadFile Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);


    }

    void Render::Run() {
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        auto gameObject = new GameObject("Cube");
        auto transform = dynamic_cast<Transform*>(gameObject->AddComponent("Transform"));

        auto mesh_filter = dynamic_cast<MeshFilter*>(gameObject->AddComponent("MeshFilter"));
        mesh_filter->LoadMesh("model/cube.mesh");

        auto material = new Material();
        material->Parse("material/cube.mat");

        mesh_render = dynamic_cast<MeshRender*>(gameObject->AddComponent("MeshRender"));
        mesh_render->SetMeshFilter(mesh_filter);
        mesh_render->SetMaterial(material);
        mesh_render->Prepare();

        auto camera_gameObject = new GameObject("Camera");
        auto camera_transform = dynamic_cast<Transform*>(camera_gameObject->AddComponent("Transform"));
        camera_transform->SetPosition(glm::vec3(0, 0, 10));
        auto camera = dynamic_cast<Camera*>(camera_gameObject->AddComponent("Camera"));
        camera->GetGameObject()->SetTag(GameObject::kTagMainCamera);

        //创建相机2 GameObject
        auto go_camera_2 = new GameObject("main_camera");
        //挂上 Transform 组件
        auto transform_camera_2 = dynamic_cast<Transform *>(go_camera_2->AddComponent("Transform"));
        transform_camera_2->SetPosition(glm::vec3(5, 0, 10));
        //挂上 Camera 组件
        auto camera_2 = dynamic_cast<Camera *>(go_camera_2->AddComponent("Camera"));

        // Main loop
#ifdef __EMSCRIPTEN__
        // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
        while (!glfwWindowShouldClose(window))
#endif
        {
            int width = 480;
            int height = 320;

            //绑定FBO进行渲染：在你的渲染循环中，当你想将内容渲染到离屏缓冲区（即FBO）时，你应该先绑定FBO。
            //创建全局FBO，将整个游戏渲染到FBO，提供给编辑器，作为Game视图显示
            GLuint frame_buffer_object_id = 0;
            glGenFramebuffers(1, &frame_buffer_object_id);
            if (frame_buffer_object_id == 0) {
                printf("CreateFBO FBO Error!");
                exit(EXIT_FAILURE);
            }
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer_object_id);
            //创建颜色纹理 Attach到FBO颜色附着点上
            glGenTextures(1, &Application::color_texture_id);
            glBindTexture(GL_TEXTURE_2D, Application::color_texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Application::color_texture_id,
                                   0);
            //创建深度纹理 Attach到FBO深度附着点上
            glGenTextures(1, &Application::depth_texture_id);
            glBindTexture(GL_TEXTURE_2D, Application::depth_texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                         nullptr);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Application::depth_texture_id,
                                   0);
            //检测帧缓冲区完整性
            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE) {
                printf("BindFBO FBO Error,Status:{} !",
                       status);//36055 = 0x8CD7 GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 附着点没有东西
                exit(EXIT_FAILURE);
            }

            //设置视口和清除缓冲区：设置合适的视口，并且清除颜色和深度缓冲区，为渲染做准备。
            glViewport(0, 0, width, height);

            //camera
            camera->SetCenter(glm::vec3(0, 0, 0));
            camera->SetUp(glm::vec3(0, 1, 0));
            camera->SetClearColor(glm::vec4(0.45f, 0.55f, 0.60f, 1.00f));
            camera->SetFov(60.f);
            camera->SetAspect(width / (float) height);
            camera->SetNear(1.f);
            camera->SetFar(1000.f);

            //设置相机2
            camera_2->SetCenter(glm::vec3(glm::vec3(transform_camera_2->GetPosition().x, 0, 0)));
            camera_2->SetUp(glm::vec3(0, 1, 0));
            camera_2->SetFov(60.f);
            camera_2->SetAspect(width / (float) height);
            camera_2->SetNear(1.f);
            camera_2->SetFar(1000.f);

            //旋转物体
            static float rotate_eulerAngle = 0.f;
            rotate_eulerAngle += 1.f;
            auto rotation = transform->GetRotation();
            rotation.y = rotate_eulerAngle;
            transform->SetRotation(rotation);

            Camera::RenderAll(mesh_render);

            //解绑FBO：完成FBO的渲染后，你通常会绑定回默认的帧缓冲区，继续渲染你的UI或其它画面内容。
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            DivineBrush::Editor::EditorWindow::GetHierarchyWindow()->GUI();
            DivineBrush::Editor::EditorWindow::GetInspectorWindow()->GUI();
            DivineBrush::Editor::EditorWindow::GetSceneWindow()->GUI();
            DivineBrush::Editor::EditorWindow::GetGameWindow()->GUI();
            DivineBrush::Editor::EditorWindow::GetProjectWindow()->GUI();
            DivineBrush::Editor::EditorWindow::GetConsoleWindow()->GUI();


//         //    2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
//        {
//            static float f = 0.0f;
//            static int counter = 0;
//
//            ImGui::Begin("Hierarchy");                          // Create a window called "Hello, world!" and append into it.
//
//            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//            ImGui::Checkbox("Another Window", &show_another_window);
//
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//                counter++;
//            ImGui::SameLine();
//            ImGui::Text("counter = %d", counter);
//
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//            ImGui::End();
//        }

            // 3. Show another simple window.
            if (show_another_window) {
                ImGui::Begin("Another Window",
                             &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
//            int display_w, display_h;
//            glfwGetFramebufferSize(window, &display_w, &display_h);
//            glViewport(0, 0, display_w, display_h);
            glViewport(0, 0, width, height);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                         clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }
#ifdef __EMSCRIPTEN__
        EMSCRIPTEN_MAINLOOP_END;
#endif

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

} // DivineBrush