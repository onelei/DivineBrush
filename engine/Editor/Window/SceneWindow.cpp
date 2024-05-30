//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "SceneWindow.h"

namespace DivineBrush::Editor {

    SceneWindow::SceneWindow() : EditorWindow(k_Scene) {

    }

    SceneWindow::~SceneWindow() {
        EditorWindow::~EditorWindow();
    }

    void SceneWindow::OnGUI() {
        if (is2D) {
            On2DGUI();
        } else {
            On3DGUI();
        }
    }

    void SceneWindow::On2DGUI() {
        // Draw grid + all lines in the canvas
        static ImVector<ImVec2> points;
        static ImVec2 scrolling(0.0f, 0.0f);
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Right, -1)) {
            auto io = EditorWindow::GetIO();
            scrolling.x += io->MouseDelta.x;
            scrolling.y += io->MouseDelta.y;
        }

        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
        canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
        draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
        //if (opt_enable_grid)
        {
            const float GRID_STEP = 64.0f;
            for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y),
                                   IM_COL32(200, 200, 200, 40));
            for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y),
                                   IM_COL32(200, 200, 200, 40));
        }
//        for (int n = 0; n < points.Size; n += 2)
//            draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
        draw_list->PopClipRect();
    }

    void SceneWindow::On3DGUI() {

        if (ImGui::IsMouseDragging(ImGuiMouseButton_Right, -1)) {
            auto io = ImGui::GetIO();
            scrolling.x += io.MouseDelta.x;
            scrolling.y += io.MouseDelta.y;
        }

        if (ImGui::IsWindowHovered() && ImGui::GetIO().MouseWheel != 0.0f) {
            zoom += ImGui::GetIO().MouseWheel * 0.1f;
            if (zoom < 0.1f) zoom = 0.1f;
        }

        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
        draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
        draw_list->PushClipRect(canvas_p0, canvas_p1, true);

        const float GRID_STEP = 64.0f;
        float angle = 60.0f * IM_PI / 180.0f; // 45度角度
        for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP) {
            ImVec2 p0 = PerspectiveTransform(ImVec2(canvas_p0.x + x, canvas_p0.y), canvas_p1, zoom, angle);
            ImVec2 p1 = PerspectiveTransform(ImVec2(canvas_p0.x + x, canvas_p1.y), canvas_p1, zoom, angle);
            draw_list->AddLine(p0, p1, IM_COL32(200, 200, 200, 40));
        }
        for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP) {
            ImVec2 p0 = PerspectiveTransform(ImVec2(canvas_p0.x, canvas_p0.y + y), canvas_p1, zoom, angle);
            ImVec2 p1 = PerspectiveTransform(ImVec2(canvas_p1.x, canvas_p0.y + y), canvas_p1, zoom, angle);
            draw_list->AddLine(p0, p1, IM_COL32(200, 200, 200, 40));
        }

        draw_list->PopClipRect();
    }

    // 透视投影函数
    ImVec2 SceneWindow::PerspectiveTransform(const ImVec2& point, const ImVec2& origin, float zoom, float angle) {
        float x = point.x - origin.x;
        float y = point.y - origin.y;
        float z = zoom;  // 这里的z是正数，表示从下往上看

        // 简单的透视投影
        float fov = 1.0f / tanf(angle / 2.0f);
        float perspectiveX = x * fov / z;
        float perspectiveY = y * fov / z;

        return ImVec2(origin.x + perspectiveX, origin.y + perspectiveY);
    }
} // DivineBrush
