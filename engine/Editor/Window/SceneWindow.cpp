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
        // Draw grid + all lines in the canvas
        static ImVector<ImVec2> points;
        static ImVec2 scrolling(0.0f, 0.0f);
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Right, -1))
        {
            auto io = EditorWindow::GetIO();
            scrolling.x += io->MouseDelta.x;
            scrolling.y += io->MouseDelta.y;
        }

        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
        //if (opt_enable_grid)
        {
            const float GRID_STEP = 64.0f;
            for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
            for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
        }
//        for (int n = 0; n < points.Size; n += 2)
//            draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
        draw_list->PopClipRect();
    }
} // DivineBrush
