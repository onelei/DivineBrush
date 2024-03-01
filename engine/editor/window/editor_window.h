//
// Created by D0800 on 2024/3/1.
//

#ifndef ENGINE_EDITOR_WINDOW_H
#define ENGINE_EDITOR_WINDOW_H

namespace DivineBrush {

    class EditorWindow {
    public:
        EditorWindow();

        ~EditorWindow();

        virtual void OnEnable();

        virtual void OnDisable();

        virtual void OnGUI();

        virtual void OnDestroy();
    };

} // DivineBrush

#endif //ENGINE_EDITOR_WINDOW_H
