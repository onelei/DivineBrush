﻿---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/5/23 17:19
---
---@class MeshFilter:Component
local MeshFilter = class("MeshFilter", Component)

function MeshFilter:ctor()
    Component.ctor(self)
end

function MeshFilter:SetCpp(...)
    ---C++组件实例
    self.cpp = Cpp.MeshFilter()
end

function MeshFilter:CreateMesh(vertex_data, vertex_index_data)
    self:GetCpp():CreateMesh(vertex_data, vertex_index_data)
end

function MeshFilter:GetMesh()
    return self:GetCpp():GetMesh()
end

function MeshFilter:GetSkinMesh()
    return self:GetCpp():GetSkinMesh()
end

function MeshFilter:GetMeshName()
    return self:GetCpp():GetMeshName()
end

function MeshFilter:SetBoneInfo(boneInfoData)
    self:GetCpp():SetBoneInfo(boneInfoData)
end

function MeshFilter:LoadWeight(filePath)
    self:GetCpp():LoadWeight(filePath)
end

return MeshFilter