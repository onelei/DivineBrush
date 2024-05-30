//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_CONSOLEWINDOW_H
#define ENGINE_CONSOLEWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    class ConsoleWindow : public EditorWindow {
    public:
        ConsoleWindow();

        ~ConsoleWindow();

        void OnGUI() override;

        void ClearLog();

        void AddLog(const char *fmt, ...) IM_FMTARGS(2);

        void ExecCommand(const char *command_line);

    private:
        char InputBuf[256];
        ImVector<char *> Items;
        ImVector<const char *> Commands;
        ImVector<char *> History;
        int HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter Filter;
        bool AutoScroll;
        bool ScrollToBottom;
    };
} // DivineBrush

#endif //ENGINE_CONSOLEWINDOW_H
