//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_SCENEWINDOW_H
#define ENGINE_SCENEWINDOW_H

#include "EditorWindow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
#include "GraphEditor.h"
#include <math.h>
#include <vector>
#include <algorithm>

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

        void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);
        // Camera projection
        bool isPerspective = true;
        float fov = 27.f;
        float viewWidth = 10.f; // for orthographic
        float camYAngle = 165.f / 180.f * 3.14159f;
        float camXAngle = 32.f / 180.f * 3.14159f;
        float cameraView[16] =
                { 1.f, 0.f, 0.f, 0.f,
                  0.f, 1.f, 0.f, 0.f,
                  0.f, 0.f, 1.f, 0.f,
                  0.f, 0.f, 0.f, 1.f };

        float cameraProjection[16];
        bool firstFrame = true;
        int gizmoCount = 1;
        float camDistance = 8.f;
        ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        int lastUsing = 0;
        float objectMatrix[4][16] = {
                { 1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        0.f, 0.f, 0.f, 1.f },

                { 1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        2.f, 0.f, 0.f, 1.f },

                { 1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        2.f, 0.f, 2.f, 1.f },

                { 1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        0.f, 0.f, 2.f, 1.f }
        };

        constexpr static const float identityMatrix[16] =
                { 1.f, 0.f, 0.f, 0.f,
                  0.f, 1.f, 0.f, 0.f,
                  0.f, 0.f, 1.f, 0.f,
                  0.f, 0.f, 0.f, 1.f };

        void Frustum(float left, float right, float bottom, float top, float znear, float zfar, float* m16)
        {
            float temp, temp2, temp3, temp4;
            temp = 2.0f * znear;
            temp2 = right - left;
            temp3 = top - bottom;
            temp4 = zfar - znear;
            m16[0] = temp / temp2;
            m16[1] = 0.0;
            m16[2] = 0.0;
            m16[3] = 0.0;
            m16[4] = 0.0;
            m16[5] = temp / temp3;
            m16[6] = 0.0;
            m16[7] = 0.0;
            m16[8] = (right + left) / temp2;
            m16[9] = (top + bottom) / temp3;
            m16[10] = (-zfar - znear) / temp4;
            m16[11] = -1.0f;
            m16[12] = 0.0;
            m16[13] = 0.0;
            m16[14] = (-temp * zfar) / temp4;
            m16[15] = 0.0;
        }

        void Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar, float* m16)
        {
            float ymax, xmax;
            ymax = znear * tanf(fovyInDegrees * 3.141592f / 180.0f);
            xmax = ymax * aspectRatio;
            Frustum(-xmax, xmax, -ymax, ymax, znear, zfar, m16);
        }

        void Cross(const float* a, const float* b, float* r)
        {
            r[0] = a[1] * b[2] - a[2] * b[1];
            r[1] = a[2] * b[0] - a[0] * b[2];
            r[2] = a[0] * b[1] - a[1] * b[0];
        }

        float Dot(const float* a, const float* b)
        {
            return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        }

        void Normalize(const float* a, float* r)
        {
            float il = 1.f / (sqrtf(Dot(a, a)) + FLT_EPSILON);
            r[0] = a[0] * il;
            r[1] = a[1] * il;
            r[2] = a[2] * il;
        }

        void LookAt(const float* eye, const float* at, const float* up, float* m16)
        {
            float X[3], Y[3], Z[3], tmp[3];

            tmp[0] = eye[0] - at[0];
            tmp[1] = eye[1] - at[1];
            tmp[2] = eye[2] - at[2];
            Normalize(tmp, Z);
            Normalize(up, Y);

            Cross(Y, Z, tmp);
            Normalize(tmp, X);

            Cross(Z, X, tmp);
            Normalize(tmp, Y);

            m16[0] = X[0];
            m16[1] = Y[0];
            m16[2] = Z[0];
            m16[3] = 0.0f;
            m16[4] = X[1];
            m16[5] = Y[1];
            m16[6] = Z[1];
            m16[7] = 0.0f;
            m16[8] = X[2];
            m16[9] = Y[2];
            m16[10] = Z[2];
            m16[11] = 0.0f;
            m16[12] = -Dot(X, eye);
            m16[13] = -Dot(Y, eye);
            m16[14] = -Dot(Z, eye);
            m16[15] = 1.0f;
        }

        void OrthoGraphic(const float l, float r, float b, const float t, float zn, const float zf, float* m16)
        {
            m16[0] = 2 / (r - l);
            m16[1] = 0.0f;
            m16[2] = 0.0f;
            m16[3] = 0.0f;
            m16[4] = 0.0f;
            m16[5] = 2 / (t - b);
            m16[6] = 0.0f;
            m16[7] = 0.0f;
            m16[8] = 0.0f;
            m16[9] = 0.0f;
            m16[10] = 1.0f / (zf - zn);
            m16[11] = 0.0f;
            m16[12] = (l + r) / (l - r);
            m16[13] = (t + b) / (b - t);
            m16[14] = zn / (zn - zf);
            m16[15] = 1.0f;
        }

        inline void rotationY(const float angle, float* m16)
        {
            float c = cosf(angle);
            float s = sinf(angle);

            m16[0] = c;
            m16[1] = 0.0f;
            m16[2] = -s;
            m16[3] = 0.0f;
            m16[4] = 0.0f;
            m16[5] = 1.f;
            m16[6] = 0.0f;
            m16[7] = 0.0f;
            m16[8] = s;
            m16[9] = 0.0f;
            m16[10] = c;
            m16[11] = 0.0f;
            m16[12] = 0.f;
            m16[13] = 0.f;
            m16[14] = 0.f;
            m16[15] = 1.0f;
        }
    };
} // DivineBrush

#endif //ENGINE_SCENEWINDOW_H
