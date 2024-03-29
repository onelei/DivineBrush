//
// Created by onelei on 2024/3/27.
//

#ifndef ENGINE_BUTTON_H
#define ENGINE_BUTTON_H

#include <functional>
#include "../Component/Component.h"
#include "Image.h"

namespace DivineBrush::UI {

    class Button : public Component {
    public:
        Button();

        ~Button();

        void OnUpdate() override;

        void SetNormalImage(Image *image) {
            normal_image = image;
        }

        void SetPressedImage(Image *image) {
            pressed_image = image;
        }

        void SetOnClickCallback(std::function<void()> func) {
            on_click_callback = func;
        }

    private:
        Image *normal_image = nullptr;
        Image *pressed_image = nullptr;
        bool is_pressed = false;
        std::function<void()> on_click_callback;
    };

} // DivineBrush

#endif //ENGINE_BUTTON_H
