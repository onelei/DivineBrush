//
// Created by onelei on 2024/3/18.
//

#ifndef ENGINE_SCREEN_H
#define ENGINE_SCREEN_H

namespace DivineBrush {

    class Screen {
    public:
        static void SetScreenSize(int width, int height);

        static int GetWidth();

        static int GetHeight();

        static void SetWidth(int width);

        static void SetHeight(int height);

        static float GetAspect();


    private:
        static int width;
        static int height;
        static float aspect;

        static void UpdateAspect();
    };

} // DivineBrush

#endif //ENGINE_SCREEN_H
