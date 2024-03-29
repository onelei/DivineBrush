//
// Created by onelei on 2024/3/16.
//

#include "Input.h"
#include <GLFW/glfw3.h>

//键盘按键枚举(Keycodes)
//GLFW的键盘按键使用宏来定义，比如：
//
//GLFW_KEY_A，GLFW_KEY_B，... GLFW_KEY_Z 代表字母键。
//GLFW_KEY_0, GLFW_KEY_1, ... GLFW_KEY_9 代表数字键。
//GLFW_KEY_ESCAPE，GLFW_KEY_ENTER等表示特殊功能键。
//更多按键，包括方向键（如GLFW_KEY_LEFT），功能键（如GLFW_KEY_F1至GLFW_KEY_F25）等。
//鼠标按钮枚举
//鼠标按钮在GLFW中也是通过宏来定义的，主要包括：
//
//GLFW_MOUSE_BUTTON_LEFT 表示鼠标左键。
//GLFW_MOUSE_BUTTON_RIGHT 表示鼠标右键。
//GLFW_MOUSE_BUTTON_MIDDLE 表示鼠标中键。
//还有GLFW_MOUSE_BUTTON_4等定义，用于表示更多的鼠标按钮，如果你的鼠标具有超过三个按钮的话。

namespace DivineBrush {
    std::unordered_map<int, int> Input::key_action_map;
    Vector2f Input::mouse_position = {0, 0};
    float Input::mouse_scroll = 0;

    void Input::RecordKey(int key, int action) {
        key_action_map[key] = action;
    }

    bool Input::GetKeyDown(int key) {
        if (key_action_map.count(key) == 0) {
            return false;
        }
        return key_action_map[key] != GLFW_RELEASE;
    }

    bool Input::GetKeyUp(int key) {
        if (key_action_map.count(key) == 0) {
            return false;
        }
        return key_action_map[key] == GLFW_RELEASE;
    }

    bool Input::GetKey(int key) {
        return key_action_map.count(key) > 0;
    }

    void Input::Update() {
        for (auto it = key_action_map.begin(); it != key_action_map.end(); /* 不在这里增加it */) {
            if (it->second == GLFW_RELEASE) {
                it = key_action_map.erase(it); // 使用正确的迭代器操作，并适当更新迭代器
            } else {
                ++it; // 仅在不删除元素时增加迭代器
            }
        }
        mouse_scroll = 0;
    }

    bool Input::GetMouseButtonDown(int button) {
        return GetKeyDown(button);
    }

    bool Input::GetMouseButtonUp(int button) {
        return GetKeyUp(button);
    }

    bool Input::GetMouseButton(int button) {
        return GetKey(button);
    }
} // DivineBrush