//
// Created by onelei on 2024/3/18.
//

#ifndef ENGINE_SCREEN_H
#define ENGINE_SCREEN_H

namespace DivineBrush {

    class Screen {
    public:

        static void SetXY(int _x, int _y);

        static int GetX() { return x; }

        static int GetY() { return y; }

        static void SetScreenSize(int width, int height);

        static int GetWidth() { return width; }

        static int GetHeight() { return height; }

        static void SetWidth(int width);

        static void SetHeight(int height);

        static float GetAspect() { return aspect; }


    private:
        static int width;
        static int height;
        static float aspect;
        static int x;
        static int y;

        static void UpdateAspect();
    };

} // DivineBrush

#endif //ENGINE_SCREEN_H
