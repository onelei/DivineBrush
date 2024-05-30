//
// Created by onelei on 2024/3/5.
//

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
        ImGuiIO &io = ImGui::GetIO();
        if (isPerspective) {
            Perspective(fov, io.DisplaySize.x / io.DisplaySize.y, 0.1f, 100.f, cameraProjection);
        } else {
            float viewHeight = viewWidth * io.DisplaySize.y / io.DisplaySize.x;
            OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, 1000.f, -1000.f, cameraProjection);
        }
        ImGuizmo::SetOrthographic(!isPerspective);
        ImGuizmo::BeginFrame();

        ImGui::SetNextWindowPos(ImVec2(1024, 100), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiCond_Appearing);

        // create a window and insert the inspector
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(320, 340), ImGuiCond_Appearing);
        ImGui::Begin("Editor");
        ImGui::Text("Camera");
        bool viewDirty = false;
        if (ImGui::RadioButton("Perspective", isPerspective)) isPerspective = true;
        ImGui::SameLine();
        if (ImGui::RadioButton("Orthographic", !isPerspective)) isPerspective = false;
        if (isPerspective) {
            ImGui::SliderFloat("Fov", &fov, 20.f, 110.f);
        } else {
            ImGui::SliderFloat("Ortho width", &viewWidth, 1, 20);
        }
        viewDirty |= ImGui::SliderFloat("Distance", &camDistance, 1.f, 10.f);
        ImGui::SliderInt("Gizmo count", &gizmoCount, 1, 4);

        if (viewDirty || firstFrame) {
            float eye[] = {cosf(camYAngle) * cosf(camXAngle) * camDistance, sinf(camXAngle) * camDistance,
                           sinf(camYAngle) * cosf(camXAngle) * camDistance};
            float at[] = {0.f, 0.f, 0.f};
            float up[] = {0.f, 1.f, 0.f};
            LookAt(eye, at, up, cameraView);
            firstFrame = false;
        }

        ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);
        if (ImGuizmo::IsUsing()) {
            ImGui::Text("Using gizmo");
        } else {
            ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "");
            ImGui::SameLine();
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
            ImGui::SameLine();
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Over rotate gizmo" : "");
            ImGui::SameLine();
            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Over scale gizmo" : "");
        }
        ImGui::Separator();
        for (int matId = 0; matId < gizmoCount; matId++) {
            ImGuizmo::SetID(matId);

            EditTransform(cameraView, cameraProjection, objectMatrix[matId], lastUsing == matId);
            if (ImGuizmo::IsUsing()) {
                lastUsing = matId;
            }
        }
        ImGui::End();
    }

    void SceneWindow::EditTransform(float *cameraView, float *cameraProjection, float *matrix,
                                    bool editTransformDecomposition) {
        static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
        static bool useSnap = false;
        static float snap[3] = {1.f, 1.f, 1.f};
        static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
        static float boundsSnap[] = {0.1f, 0.1f, 0.1f};
        static bool boundSizing = false;
        static bool boundSizingSnap = false;

        if (editTransformDecomposition) {
            if (ImGui::IsKeyPressed(ImGuiKey_T))
                mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
            if (ImGui::IsKeyPressed(ImGuiKey_E))
                mCurrentGizmoOperation = ImGuizmo::ROTATE;
            if (ImGui::IsKeyPressed(ImGuiKey_R)) // r Key
                mCurrentGizmoOperation = ImGuizmo::SCALE;
            if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
                mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
            ImGui::SameLine();
            if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
                mCurrentGizmoOperation = ImGuizmo::ROTATE;
            ImGui::SameLine();
            if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
                mCurrentGizmoOperation = ImGuizmo::SCALE;
            float matrixTranslation[3], matrixRotation[3], matrixScale[3];
            ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
            ImGui::InputFloat3("Tr", matrixTranslation);
            ImGui::InputFloat3("Rt", matrixRotation);
            ImGui::InputFloat3("Sc", matrixScale);
            ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

            if (mCurrentGizmoOperation != ImGuizmo::SCALE) {
                if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
                    mCurrentGizmoMode = ImGuizmo::LOCAL;
                ImGui::SameLine();
                if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
                    mCurrentGizmoMode = ImGuizmo::WORLD;
            }
            if (ImGui::IsKeyPressed(ImGuiKey_S))
                useSnap = !useSnap;
            ImGui::Checkbox("##UseSnap", &useSnap);
            ImGui::SameLine();

            switch (mCurrentGizmoOperation) {
                case ImGuizmo::TRANSLATE:
                    ImGui::InputFloat3("Snap", &snap[0]);
                    break;
                case ImGuizmo::ROTATE:
                    ImGui::InputFloat("Angle Snap", &snap[0]);
                    break;
                case ImGuizmo::SCALE:
                    ImGui::InputFloat("Scale Snap", &snap[0]);
                    break;
            }
            ImGui::Checkbox("Bound Sizing", &boundSizing);
            if (boundSizing) {
                ImGui::PushID(3);
                ImGui::Checkbox("##BoundSizing", &boundSizingSnap);
                ImGui::SameLine();
                ImGui::InputFloat3("Snap", boundsSnap);
                ImGui::PopID();
            }
        }

        ImGuiIO &io = ImGui::GetIO();
        float viewManipulateRight = io.DisplaySize.x;
        float viewManipulateTop = 0;
        static ImGuiWindowFlags gizmoWindowFlags = 0;
        ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_Appearing);
        ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_Appearing);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4) ImColor(0.35f, 0.3f, 0.3f));
        ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
        ImGuizmo::SetDrawlist();
        float windowWidth = (float) ImGui::GetWindowWidth();
        float windowHeight = (float) ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
        viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
        viewManipulateTop = ImGui::GetWindowPos().y;
        ImGuiWindow *window = ImGui::GetCurrentWindow();
        gizmoWindowFlags =
                ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max)
                ? ImGuiWindowFlags_NoMove : 0;
        ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);
        ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], gizmoCount);
        ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL,
                             useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL,
                             boundSizingSnap ? boundsSnap : NULL);

        ImGuizmo::ViewManipulate(cameraView, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop),
                                 ImVec2(128, 128), 0x10101010);
        ImGui::End();
        ImGui::PopStyleColor(1);
    }


} // DivineBrush
