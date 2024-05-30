//
// Created by onelei on 2024/3/5.
//

#include "imgui.h"
#include "ProjectWindow.h"

namespace DivineBrush::Editor {
    ProjectWindow::ProjectWindow() : EditorWindow(k_Project) {

    }

    ProjectWindow::~ProjectWindow() {
        EditorWindow::~EditorWindow();
    }

    void ProjectWindow::DrawFolderTree(const FileNode &node) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        if (!node.isFolder) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }
        bool nodeOpen = ImGui::TreeNodeEx(node.name, flags);
        if (ImGui::IsItemClicked()) {
            selectedFolder = &node;
        }
        if (nodeOpen) {
            for (const auto &child: node.children) {
                DrawFolderTree(child);
            }
            ImGui::TreePop();
        }
    }

    // 绘制文件列表
    void ProjectWindow::DrawFileList(const FileNode &folder) {
        ImGui::BeginTable("FileTable", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders);
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);

        ImGui::TableHeadersRow();

        for (const auto &node: folder.children) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", node.name);
            ImGui::TableNextColumn();
            ImGui::Text("%s", node.isFolder ? "Folder" : "File");
        }

        ImGui::EndTable();
    }

    void ProjectWindow::OnGUI() {
        // 左边文件夹树
        ImGui::BeginChild("FolderTree", ImVec2(200, 0), true);
        for (const auto &node: fileSystem) {
            DrawFolderTree(node);
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // 右边文件列表
        ImGui::BeginChild("FileList", ImVec2(0, 0), true);
        if (selectedFolder) {
            DrawFileList(*selectedFolder);
        }
        ImGui::EndChild();
    }

} // DivineBrush