//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "ConsoleWindow.h"

namespace DivineBrush::Editor {
    // Portable helpers
    static int Stricmp(const char *s1, const char *s2) {
        int d;
        while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) {
            s1++;
            s2++;
        }
        return d;
    }

    static int Strnicmp(const char *s1, const char *s2, int n) {
        int d = 0;
        while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) {
            s1++;
            s2++;
            n--;
        }
        return d;
    }

    static char *Strdup(const char *s) {
        IM_ASSERT(s);
        size_t len = strlen(s) + 1;
        void *buf = ImGui::MemAlloc(len);
        IM_ASSERT(buf);
        return (char *) memcpy(buf, (const void *) s, len);
    }

    static void Strtrim(char *s) {
        char *str_end = s + strlen(s);
        while (str_end > s && str_end[-1] == ' ') str_end--;
        *str_end = 0;
    }

    ConsoleWindow::ConsoleWindow() : EditorWindow(k_Console) {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");
        AutoScroll = true;
        ScrollToBottom = false;
        AddLog("Welcome to the World!");
        AddLog("[warn] This is Warning Test.");
        AddLog("[error] This is Error Test.");
        AddLog("OK");
    }

    ConsoleWindow::~ConsoleWindow() {
        EditorWindow::~EditorWindow();
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            ImGui::MemFree(History[i]);
    }

    void ConsoleWindow::ClearLog() {
        for (int i = 0; i < Items.Size; i++)
            ImGui::MemFree(Items[i]);
        Items.clear();
    }

    void ConsoleWindow::AddLog(const char *fmt, ...) {
        // FIXME-OPT
        char buf[1024];
        va_list args;
                va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf) - 1] = 0;
                va_end(args);
        Items.push_back(Strdup(buf));
    }

    void ConsoleWindow::ExecCommand(const char *command_line) {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back.
        // This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size - 1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0) {
                ImGui::MemFree(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0) {
            ClearLog();
        } else if (Stricmp(command_line, "HELP") == 0) {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        } else if (Stricmp(command_line, "HISTORY") == 0) {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        } else {
            AddLog("Unknown command: '%s'\n", command_line);
        }

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    void ConsoleWindow::OnGUI() {
        if (ImGui::Button("Clear")) { ClearLog(); }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::Button("Copy");
//        static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }
        //ImGui::Separator();
        // Options menu
        ImGui::SameLine();
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }
        // Options, Filter
        ImGui::SameLine();
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O);
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::Separator();

        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), ImGuiChildFlags_None,
                              ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NavFlattened)) {
            if (ImGui::BeginPopupContextWindow()) {
                if (ImGui::Selectable("Clear")) ClearLog();
                ImGui::EndPopup();
            }

            // Display every line as a separate entry so we can change their color or add custom widgets.
            // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
            // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
            // to only process visible items. The clipper will automatically measure the height of your first item and then
            // "seek" to display only items in the visible area.
            // To use the clipper we can replace your standard loop:
            //      for (int i = 0; i < Items.Size; i++)
            //   With:
            //      ImGuiListClipper clipper;
            //      clipper.Begin(Items.Size);
            //      while (clipper.Step())
            //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            // - That your items are evenly spaced (same height)
            // - That you have cheap random access to your elements (you can access them given their index,
            //   without processing all the ones before)
            // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
            // We would need random-access on the post-filtered list.
            // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
            // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
            // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
            // to improve this example code!
            // If your items are of variable height:
            // - Split them into same height items would be simpler and facilitate random-seeking into your list.
            // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                ImGui::LogToClipboard();
            for (const char *item: Items) {
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;
                if (strstr(item, "[error]")) {
                    color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
                    has_color = true;
                }
                else if (strstr(item, "[warn]")) {
                    color = ImVec4(1.0f, 0.8f, 0.2f, 1.0f);
                    has_color = true;
                }
                else if (strncmp(item, "# ", 2) == 0) {
                    color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
                    has_color = true;
                }
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item);
                if (has_color)
                    ImGui::PopStyleColor();
            }
            if (copy_to_clipboard)
                ImGui::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
    }


} // DivineBrush