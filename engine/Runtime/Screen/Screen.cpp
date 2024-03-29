//
// Created by onelei on 2024/3/18.
//

#include "Screen.h"

namespace DivineBrush {
    int Screen::x;
    int Screen::y;
    int Screen::width;
    int Screen::height;
    float Screen::aspect;

    void Screen::SetXY(int _x, int _y) {
        x = _x;
        y = _y;
    }

    void Screen::SetScreenSize(int _width, int _height) {
        width = _width;
        height = _height;
        UpdateAspect();
    }

    void Screen::SetWidth(int _width) {
        width = _width;
        UpdateAspect();
    }

    void Screen::SetHeight(int _height) {
        height = _height;
        UpdateAspect();
    }

    void Screen::UpdateAspect() {
        aspect = width / (float) height;
    }

} // DivineBrush