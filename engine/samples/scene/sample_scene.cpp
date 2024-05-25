//
// Created by onelei on 2024/3/18.
//

#include <glm/ext/matrix_transform.hpp>
#include "sample_scene.h"
#include "rttr/registration.h"
#include "../../Runtime/Screen/Screen.h"
#include "../../Runtime/UI/Font.h"
#include "../../Runtime/Input/Input.h"
#include "../../Runtime/UI/Image.h"
#include "../../Runtime/UI/Mask.h"
#include "../../Runtime/UI/Text.h"
#include "../../Runtime/UI/Button.h"
#include "../../Runtime/Binder/LuaBinder.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<SampleScene>("SampleScene")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    SampleScene::SampleScene() {

    }

    void SampleScene::OnAwake() {
        auto gameObject = new GameObject("Cube");
        transform = gameObject->GetComponent<Transform>();

        auto mesh_filter = gameObject->AddComponent<MeshFilter>();
        mesh_filter->LoadMesh("model/cube.mesh");

        auto material = new Material();
        material->Parse("material/cube.mat");

        auto mesh_render = gameObject->AddComponent<MeshRenderer>();
        mesh_render->SetMeshFilter(mesh_filter);
        mesh_render->SetMaterial(material);

        auto camera_gameObject = new GameObject("Camera");
        camera_transform = camera_gameObject->GetComponent<Transform>();
        camera_transform->SetPosition(glm::vec3(0, 0, 10));
        camera = camera_gameObject->AddComponent<Camera>();
        camera->GetGameObject()->SetTag(GameObject::kTagMainCamera);
        camera->SetDepth(0);

        //创建相机2 GameObject
//        auto go_camera_2 = new GameObject("main_camera");
//        //挂上 Transform 组件
//        transform_camera_2 = dynamic_cast<Transform *>(go_camera_2->AddComponent("Transform"));
//        transform_camera_2->SetPosition(glm::vec3(1, 0, 10));
//        //挂上 Camera 组件
//        camera_2 = dynamic_cast<Camera *>(go_camera_2->AddComponent("Camera"));
//        camera_2->SetDepth(1);
        //camera_2->SetCullingMask(0x02);
        mousePosition = Input::GetMousePosition();

        CreateFont();

        CreateUI();

        auto luaBinder = new LuaBinder();
        luaBinder->Init();
    }

    void SampleScene::OnUpdate() {
        //camera
        camera->SetCenter(glm::vec3(0, 0, 0));
        camera->SetUp(glm::vec3(0, 1, 0));
        camera->SetClearColor(glm::vec4(0.45f, 0.55f, 0.60f, 1.00f));
        camera->SetFov(60.f);
        camera->SetAspect(Screen::GetAspect());
        camera->SetNear(1.f);
        camera->SetFar(1000.f);

        //设置相机2
//        camera_2->SetCenter(glm::vec3(glm::vec3(transform_camera_2->GetPosition().x, 0, 0)));
//        camera_2->SetUp(glm::vec3(0, 1, 0));
//        camera_2->SetFov(60.f);
//        camera_2->SetAspect(Screen::GetAspect());
//        camera_2->SetNear(1.f);
//        camera_2->SetFar(1000.f);

        if (Input::GetKeyUp(GLFW_KEY_A)) {
            auto pGameObject = GameObject::Find("mask");
            if (pGameObject == nullptr) {
                return;
            }
            pGameObject->SetActive(!pGameObject->IsActive());
        }

        //旋转物体
        if (Input::GetKeyDown(GLFW_KEY_R)) {
            auto rotate_eulerAngle = Input::GetMousePosition().x - mousePosition.x;
            auto rotation = transform->GetRotation();
            rotation.y = rotate_eulerAngle;
            transform->SetRotation(rotation);
        }

        //旋转相机
        if (Input::GetKeyDown(GLFW_KEY_LEFT_ALT) && Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            float degrees = Input::GetMousePosition().x - mousePosition.x;

            glm::mat4 old_mat4 = glm::mat4(1.0f);
            //以相机所在坐标系位置，计算用于旋转的矩阵，这里是零点，所以直接用方阵。
            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec4 old_pos = glm::vec4(camera_transform->GetPosition(), 1.0f);
            glm::vec4 new_pos = rotate_mat4 * old_pos;//旋转矩阵 * 原来的坐标 = 相机以零点做旋转。

            camera_transform->SetPosition(glm::vec3(new_pos));
        }

        mousePosition = Input::GetMousePosition();
        camera_transform->SetPosition(camera_transform->GetPosition() * (10 - Input::GetMouseScroll()) / 10.f);
    }

    void SampleScene::CreateFont() {
        //生成文字贴图
        auto font = Font::Load("font/hkyuan.ttf", 20);
        std::string str = "Brush";
        auto characters = font->LoadString(str);
        int offset = 0;
        for (auto character: characters) {
            offset += 2;
            //std::cout << "Character: " << ch << " " << character->left_top_x_ << " " << character->left_top_y_ << " " << character->right_bottom_x_ << " " << character->right_bottom_y_ << std::endl;
            //offset += character->right_bottom_x_ - character->left_top_x_;
            //因为FreeType生成的bitmap是上下颠倒的，所以这里UV坐标也要做对应翻转，将左上角作为零点。
            std::vector<MeshFilter::Vertex> vertex_vector = {
//                    {{-1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//                    {{1.0f,  -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//                    {{1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//                    {{-1.0f, 1.0f,  1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}

                    {{-1.0f +
                      offset, 2.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {character->left_top_x,     character->left_top_y}},
                    {{1.0f +
                      offset, 2.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {character->right_bottom_x, character->left_top_y}},
                    {{1.0f +
                      offset, 4.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {character->right_bottom_x, character->right_bottom_y}},
                    {{-1.0f +
                      offset, 4.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {character->left_top_x,     character->right_bottom_y}}
            };
            std::vector<unsigned short> index_vector = {
                    0, 1, 2,
                    0, 2, 3
            };
            //创建模型 GameObject
            auto go = new GameObject("font");
            go->SetLayer(0x01);
            //挂上 Transform 组件
            auto transform = go->GetComponent<Transform>();
            transform->SetPosition({-8.f, 0.f, 0.f});
            //挂上 MeshFilter 组件
            auto mesh_filter = go->AddComponent<MeshFilter>();
            mesh_filter->CreateMesh(vertex_vector, index_vector);
            //创建 Material
            auto material = new Material();//设置材质
            material->Parse("material/font.mat");
            //挂上 MeshRenderer 组件
            auto mesh_renderer = go->AddComponent<MeshRenderer>();
            mesh_renderer->SetMaterial(material);
            mesh_renderer->SetMeshFilter(mesh_filter);
            //使用文字贴图
            material->SetTexture("u_diffuse_texture", font->GetFontTexture());
        }
    }

    bool is_pressed = false;

    void SampleScene::CreateUI() {
        //创建UI相机 GameObject
        auto go_camera_ui = new GameObject("ui_camera");
        //挂上 Transform 组件
        auto transform_camera_ui = go_camera_ui->GetComponent<Transform>();
        transform_camera_ui->SetPosition(glm::vec3(0, 0, 10));
        //挂上 Camera 组件
        auto camera_ui = go_camera_ui->AddComponent<Camera>();
        camera_ui->SetDepth(1);
        camera_ui->SetCullingMask(0x02);
        //UI相机不能清除之前的颜色。不然用第一个相机矩阵渲染的物体就被清除 没了。
        camera_ui->SetClearFlag(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //设置正交相机
        camera_ui->SetCenter(glm::vec3(0, 0, 0));
        camera_ui->SetUp(glm::vec3(0, 1, 0));
        camera_ui->SetOrthographic(-Screen::GetWidth() / 2, Screen::GetWidth() / 2, -Screen::GetHeight() / 2,
                                   Screen::GetHeight() / 2);
        camera_ui->SetNear(-100);
        camera_ui->SetFar(100);
        camera_ui->SetMode(Camera::CameraMode::Orthographic);

        //创建 image
        auto go = new GameObject("image");
        go->SetLayer(0x02);
        //挂上 Image 组件
        auto image = go->AddComponent<UI::Image>();
        //Texture2d::CompressFile("image/image2.png", "image/image2.glt");
        image->Load("image/image2.glt");

        //创建 GameObject
        auto go_mask = new GameObject("mask");
        go_mask->SetLayer(0x02);
        go_mask->SetParent(go);
        //挂上 Mask 组件
        auto mask = go_mask->AddComponent<UI::Mask>();
        //Texture2d::CompressFile("image/mask.png", "image/mask.glt");
        mask->Load("image/mask.glt");


        //生成文字贴图
        Font *font = Font::Load("font/hkyuan.ttf", 24);
        //创建 GameObject
        auto go_ui_text = new GameObject("text");
        go_ui_text->SetLayer(0x02);
        //挂上 Transform 组件
        auto transform_ui_text = go_ui_text->GetComponent<Transform>();
        transform_ui_text->SetPosition({0.f, -20.f, 0});
        //挂上 UIText 组件
        auto ui_text = go_ui_text->AddComponent<UI::Text>();
        ui_text->SetFont(font);
        ui_text->SetText("looks good");
        ui_text->SetColor({1, 0, 0, 1});

        //创建按钮普通状态图片
        auto go_button_image_normal = new GameObject("button_normal");
        go_button_image_normal->SetLayer(0x02);
        auto ui_image_button_image_normal = go_button_image_normal->AddComponent<UI::Image>();
        //Texture2d::CompressFile("image/02.png", "image/02.cpt");
        ui_image_button_image_normal->SetTexture2d(Texture2d::LoadCompressFile("image/02.cpt"));
        //创建按钮按下状态图片
        auto go_button_image_normal_press = new GameObject("button_press");
        go_button_image_normal_press->SetLayer(0x02);
        auto ui_image_button_image_normal_press = go_button_image_normal_press->AddComponent<UI::Image>();
        //Texture2d::CompressFile("image/03.png", "image/03.cpt");
        ui_image_button_image_normal_press->SetTexture2d(Texture2d::LoadCompressFile("image/03.cpt"));
        //创建按钮
        auto go_ui_button = new GameObject("button");
        go_ui_button->SetLayer(0x02);
        auto transform_ui_button = go_ui_button->GetComponent<Transform>();
        transform_ui_button->SetPosition({0.f, 0.f, 0});
        auto ui_button = go_ui_button->AddComponent<UI::Button>();
        ui_button->SetNormalImage(ui_image_button_image_normal);
        ui_button->SetPressedImage(ui_image_button_image_normal_press);
        ui_button->SetOnClickCallback([=]() {
            is_pressed = !is_pressed;
            ui_text->SetText("is pressed: " + std::to_string(is_pressed));
        });
    }

    void SampleScene::OnDestroy() {
        Component::OnDestroy();
    }

} // DivineBrush