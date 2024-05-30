//
// Created by onelei on 2024/3/28.
//

#ifndef ENGINE_RECTINT_H
#define ENGINE_RECTINT_H
namespace DivineBrush {
    struct RectInt {
        int x, y, width, height;

        int xMin() const { return x; }

        int xMax() const { return x + width; }

        int yMin() const { return y; }

        int yMax() const { return y + height; }
    };
}//DivineBrush
#endif //ENGINE_RECTINT_H
