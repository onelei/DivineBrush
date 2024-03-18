//
// Created by onelei on 2024/3/18.
//

#include "screen.h"

namespace DivineBrush {
    int Screen::width;
    int Screen::height;
    float Screen::aspect;

    void Screen::SetScreenSize(int _width, int _height) {
        width = _width;
        height = _height;
        UpdateAspect();
    }

    int Screen::GetWidth() {
        return width;
    }

    int Screen::GetHeight() {
        return height;
    }

    void Screen::SetWidth(int _width) {
        width = _width;
        UpdateAspect();
    }

    void Screen::SetHeight(int _height) {
        height = _height;
        UpdateAspect();
    }

    float Screen::GetAspect() {
        return aspect;
    }

    void Screen::UpdateAspect() {
        aspect = width / (float) height;
    }

} // DivineBrush