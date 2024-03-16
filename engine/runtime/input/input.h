//
// Created by onelei on 2024/3/16.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <unordered_map>

namespace DivineBrush {
    struct Vector2f {
        float x, y;
    };

    class Input {
    public:
        static void RecordKey(int key, int action);

        static void Update();

        static bool GetKeyDown(int key);

        static bool GetKeyUp(int key);

        static bool GetKey(int key);

        static bool GetMouseButtonDown(int button);

        static bool GetMouseButtonUp(int button);

        static bool GetMouseButton(int button);

//        static float GetAxis(const char* axisName);
//
//        static void SetCursorVisible(bool visible);
//        static void SetCursorLock(bool lock);

        static void SetMousePosition(float x, float y) {
            mouse_position.x = x;
            mouse_position.y = y;
        }

        static Vector2f GetMousePosition() {
            return mouse_position;
        }

        static void SetMouseScroll(float value) {
            mouse_scroll += value;
        }

        static float GetMouseScroll() {
            return mouse_scroll;
        }

    private:
        static std::unordered_map<int, int> key_action_map;
        static Vector2f mouse_position;
        static float mouse_scroll;
    };

} // DivineBrush

#endif //ENGINE_INPUT_H
