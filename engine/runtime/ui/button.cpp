//
// Created by onelei on 2024/3/27.
//

#include "button.h"
#include "../object/transform.h"
#include "../object/game_object.h"
#include "../input/input.h"
#include "../screen/screen.h"
#include "rttr/registration.h"

namespace DivineBrush::UI {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Button>("Button")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Button::Button() {

    }

    Button::~Button() {

    }

    void Button::OnUpdate() {
        if (normal_image == nullptr || pressed_image == nullptr) {
            return;
        }
        Component::OnUpdate();
        auto transform = dynamic_cast<Transform *>(gameObject->GetComponent("Transform"));
        //按钮的图片 与 按钮坐标同步
        auto transform_image_normal = dynamic_cast<Transform *>(normal_image->GetGameObject()->GetComponent(
                "Transform"));
        auto transform_image_press = dynamic_cast<Transform *>(pressed_image->GetGameObject()->GetComponent(
                "Transform"));
        transform_image_normal->SetPosition(transform->GetPosition());
        transform_image_press->SetPosition(transform->GetPosition());
        is_pressed = false;
        if (Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            auto transform_position = transform->GetPosition();
            //获取鼠标坐标，并从左上角零点，转换为屏幕中心零点。
            auto mouse_position = Input::GetMousePosition();
            mouse_position.x -= Screen::GetX();
            mouse_position.y -= Screen::GetY();
            mouse_position.x = mouse_position.x - Screen::GetWidth() / 2;
            mouse_position.y = Screen::GetHeight() / 2 - mouse_position.y;
            //获取按钮图片宽高
            auto image_normal_width_half = normal_image->GetTexture2d()->GetWidth();
            auto image_normal_height_half = pressed_image->GetTexture2d()->GetHeight();
            //计算鼠标点击是否在按钮图片范围内
            if ((mouse_position.x > (transform_position.x) &&
                 mouse_position.x < (transform_position.x + image_normal_width_half)) &&
                mouse_position.y < (transform_position.y) &&
                 mouse_position.y > (transform_position.y - image_normal_height_half)) {
                if (is_pressed) {
                    return;
                }
                is_pressed = true;
                //触发按钮点击回调
                if (on_click_callback != nullptr) {
                    on_click_callback();
                }
            }
        }
        //当press为true 关闭普通状态图片，激活按下状态图片.否则反转。
        transform_image_normal->GetGameObject()->SetActive(!is_pressed);
        transform_image_press->GetGameObject()->SetActive(is_pressed);
    }
} // DivineBrush