//
// Created by onelei on 2024/5/31.
//

#ifndef ENGINE_TOPBARWINDOW_H
#define ENGINE_TOPBARWINDOW_H

#include "EditorWindow.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "imgui.h"

namespace DivineBrush::Editor {
    class TopBarWindow : public EditorWindow {
    public:
        TopBarWindow();

        ~TopBarWindow() override;

        void OnGUI() override;

    private:
        void *dragButtonTextureId = nullptr;
        void *moveButtonTextureId = nullptr;
        void *rotateButtonTextureId = nullptr;
        void *scaleButtonTextureId = nullptr;
        void *rectButtonTextureId = nullptr;

        void *playButtonTextureId = nullptr;
        void *pauseButtonTextureId = nullptr;
        void *nextButtonTextureId = nullptr;
    };
}// DivineBrush::Editor

#endif //ENGINE_TOPBARWINDOW_H
