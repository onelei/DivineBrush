---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/4/3 17:54
---
---@class Transform:Component
local Transform = class("Transform", Component)

function Transform:ctor()
    ---self.position = { x = 0, y = 0, z = 0 }
    ---self.rotation = { x = 0, y = 0, z = 0 }
    ---self.scale = { x = 1, y = 1, z = 1 }
    Component.ctor(self)
end

function Transform:SetCpp()
    self.cpp = Cpp.Transform()
end

function Transform:GetPosition()
    return self:GetCpp():GetPosition()
end

function Transform:SetPosition(position)
    self:GetCpp():SetPosition(position)
end

function Transform:GetRotation()
    return self:GetCpp():GetRotation()
end

function Transform:SetRotation(rotation)
    self:GetCpp():SetPosition(rotation)
end

function Transform:GetScale()
    return self:GetCpp():GetScale()
end

function Transform:SetScale(scale)
    self:GetCpp():SetScale(scale)
end

return Transform