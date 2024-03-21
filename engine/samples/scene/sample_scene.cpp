//
// Created by onelei on 2024/3/18.
//

#include <glm/ext/matrix_transform.hpp>
#include "sample_scene.h"
#include "rttr/registration.h"
#include "../../runtime/screen/screen.h"
#include "../../runtime/font/font.h"
#include "../../runtime/input/input.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<SampleScene>("SampleScene")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    SampleScene::SampleScene() {

    }

    void SampleScene::Awake() {
        auto gameObject = new GameObject("Cube");
        transform = dynamic_cast<Transform *>(gameObject->AddComponent("Transform"));

        auto mesh_filter = dynamic_cast<MeshFilter *>(gameObject->AddComponent("MeshFilter"));
        mesh_filter->LoadMesh("model/cube.mesh");

        auto material = new Material();
        material->Parse("material/cube.mat");

        auto mesh_render = dynamic_cast<MeshRender *>(gameObject->AddComponent("MeshRender"));
        mesh_render->SetMeshFilter(mesh_filter);
        mesh_render->SetMaterial(material);
        mesh_render->Prepare();

        auto camera_gameObject = new GameObject("Camera");
        camera_transform = dynamic_cast<Transform *>(camera_gameObject->AddComponent("Transform"));
        camera_transform->SetPosition(glm::vec3(0, 0, 10));
        camera = dynamic_cast<Camera *>(camera_gameObject->AddComponent("Camera"));
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
    }

    void SampleScene::Update() {
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

    void SampleScene::Destroy() {

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
                      offset, 4.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {character->right_bottom_x, character->right_bottom_y}},
                    {{-1.0f +
                      offset, 4.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {character->left_top_x,     character->right_bottom_y}}
            };
            std::vector<unsigned short> index_vector = {
                    0, 1, 2,
                    0, 2, 3
            };
            //创建模型 GameObject
            auto go = new GameObject("font");
            go->SetLayer(0x01);
            //挂上 Transform 组件
            auto transform = dynamic_cast<Transform *>(go->AddComponent("Transform"));
            transform->SetPosition({-8.f, 0.f, 0.f});
            //挂上 MeshFilter 组件
            auto mesh_filter = dynamic_cast<MeshFilter *>(go->AddComponent("MeshFilter"));
            mesh_filter->CreateMesh(vertex_vector, index_vector);
            //创建 Material
            auto material = new Material();//设置材质
            material->Parse("material/font.mat");
            //挂上 MeshRenderer 组件
            auto mesh_renderer = dynamic_cast<MeshRender *>(go->AddComponent("MeshRender"));
            mesh_renderer->SetMaterial(material);
            mesh_renderer->SetMeshFilter(mesh_filter);
            mesh_renderer->Prepare();
            //使用文字贴图
            material->SetTexture("u_diffuse_texture", font->GetFontTexture());
        }
    }

} // DivineBrush