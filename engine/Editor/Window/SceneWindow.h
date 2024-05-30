//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_SCENEWINDOW_H
#define ENGINE_SCENEWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    class SceneWindow : public EditorWindow {
    public:
        SceneWindow();

        ~SceneWindow();

        void OnGUI() override;

        void On2DGUI();

        void On3DGUI();

    private:
        ImVec2 canvas_sz;
        bool is2D = false;

        ImVector<ImVec2> points;
        ImVec2 scrolling = ImVec2(0.0f, 0.0f);
        float zoom = 1.0f;
        float perspective_factor = 0.001f;
        // 透视投影函数
        ImVec2 PerspectiveTransform(const ImVec2& point, const ImVec2& origin, float zoom, float angle);

    };
} // DivineBrush

#endif //ENGINE_SCENEWINDOW_H
