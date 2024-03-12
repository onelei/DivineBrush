//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "render/render.h"

namespace DivineBrush {
    class Application {
    public:
        static Application &GetInstance() {
            static Application instance;
            return instance;
        }

        void Init();

        void Update();

        void Render();

        void UpdateScreenSize();

        void Run();

        class Render *GetRender(){
            return render;
        }

    private:
        // 私有化构造函数
        Application() = default;

        // 禁止拷贝
        Application(const Application &) = delete;

        // 禁止赋值
        Application &operator=(const Application &) = delete;

        class Render *render;
    };
} // DivineBrush

#endif //ENGINE_APPLICATION_H
