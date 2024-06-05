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
        On3DGUI();
    }

    void SceneWindow::On3DGUI() {
        auto io = EditorWindow::GetIO();
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Shaded")) {
                if (ImGui::MenuItem("New", "Ctrl+N")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S")) {}
                if (ImGui::MenuItem("Exit", "Alt+F4")) {}
                ImGui::EndMenu();
            }

            if (ImGui::SmallButton(isPerspective ? "3D" : "2D")) {
                isPerspective = !isPerspective;
            }
        }
        ImGui::EndMenuBar();

        if (isPerspective) {
            Perspective(fov, io->DisplaySize.x / io->DisplaySize.y, 0.1f, 100.f, cameraProjection);
        } else {
            float viewHeight = viewWidth * io->DisplaySize.y / io->DisplaySize.x;
            OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, 1000.f, -1000.f, cameraProjection);
        }
        ImGuizmo::SetOrthographic(!isPerspective);
        //ImGuizmo::BeginFrame();
        //ImGui::SetNextWindowPos(ImVec2(1024, 100), ImGuiCond_Appearing);
        //ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiCond_Appearing);

        // create a window and insert the inspector
        //ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
        //ImGui::SetNextWindowSize(ImVec2(320, 340), ImGuiCond_Appearing);
        //ImGui::Begin("Editor");
        //ImGui::Text("Camera");

        bool viewDirty = false;
        if (io->MouseWheel != 0) {
            if (isPerspective) {
                camDistance += io->MouseWheel * 0.1f;
                camDistance = ImClamp(camDistance, 1.0f, 10.0f);
            } else {
                viewWidth += io->MouseWheel * 0.1f;
                viewWidth = ImClamp(viewWidth, 1.0f, 20.0f);
            }
            viewDirty = true;
        }
        //ImGui::SliderFloat("Fov", &fov, 20.f, 110.f);
        //viewDirty |= ImGui::SliderFloat("Distance", &camDistance, 1.f, 10.f);
        //ImGui::SliderInt("Gizmo count", &gizmoCount, 1, 4);

        if (viewDirty || firstFrame) {
            float eye[] = {cosf(camYAngle) * cosf(camXAngle) * camDistance, sinf(camXAngle) * camDistance,
                           sinf(camYAngle) * cosf(camXAngle) * camDistance};
            float at[] = {0.f, 0.f, 0.f};
            float up[] = {0.f, 1.f, 0.f};
            LookAt(eye, at, up, cameraView);
            firstFrame = false;
        }

//        ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);
//        if (ImGuizmo::IsUsing()) {
//            ImGui::Text("Using gizmo");
//        } else {
//            ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "");
//            ImGui::SameLine();
//            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
//            ImGui::SameLine();
//            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Over rotate gizmo" : "");
//            ImGui::SameLine();
//            ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Over scale gizmo" : "");
//        }
//        ImGui::Separator();
        for (int matId = 0; matId < gizmoCount; matId++) {
            ImGuizmo::SetID(matId);

            EditTransform(cameraView, cameraProjection, objectMatrix[matId], lastUsing == matId);
            if (ImGuizmo::IsUsing()) {
                lastUsing = matId;
            }
        }
        //ImGui::End();
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
            if (ImGui::IsKeyPressed(ImGuiKey_S))
                useSnap = !useSnap;
            ImGui::Checkbox("##UseSnap", &useSnap);
            ImGui::SameLine();

//            switch (mCurrentGizmoOperation) {
//                case ImGuizmo::TRANSLATE:
//                    ImGui::InputFloat3("Snap", &snap[0]);
//                    break;
//                case ImGuizmo::ROTATE:
//                    ImGui::InputFloat("Angle Snap", &snap[0]);
//                    break;
//                case ImGuizmo::SCALE:
//                    ImGui::InputFloat("Scale Snap", &snap[0]);
//                    break;
//            }
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
        //ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
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
        //ImGui::End();
        ImGui::PopStyleColor(1);
    }


} // DivineBrush
