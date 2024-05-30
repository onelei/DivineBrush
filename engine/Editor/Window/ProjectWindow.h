//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_PROJECTWINDOW_H
#define ENGINE_PROJECTWINDOW_H

#include <imgui.h>
#include "EditorWindow.h"

namespace DivineBrush::Editor {
    // 示例文件夹和文件结构
    struct FileNode {
        const char *name;
        bool isFolder;
        std::vector<FileNode> children;
    };

    class ProjectWindow : public EditorWindow {
    public:
        ProjectWindow();

        ~ProjectWindow();

        void OnGUI() override;

    private:
        // 递归绘制文件夹树
        void DrawFolderTree(const FileNode &node);

        // 绘制文件列表
        void DrawFileList(const FileNode &folder);

        // 当前选中的文件夹
        const FileNode *selectedFolder = nullptr;
        // 示例文件系统
        std::vector<FileNode> fileSystem = {
                {"Assets", true, {
                                         {"Scripts",      true,  {
                                                                         {"main.cpp", false, {}},
                                                                         {"utils.cpp", false, {}},
                                                                 }},
                                         {"Textures",     true,  {
                                                                         {"texture1.png", false, {}},
                                                                         {"texture2.png", false, {}},
                                                                 }},
                                 }},
                {"Scenes", true, {
                                         {"scene1.unity", false, {}},
                                         {"scene2.unity", false, {}},
                                 }},
        };
    };
} // DivineBrush

#endif //ENGINE_PROJECTWINDOW_H
