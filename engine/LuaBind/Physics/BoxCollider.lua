﻿---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/5/8 11:05
---
---@class BoxCollider
local BoxCollider = class("BoxCollider", Collider)

function BoxCollider:ctor()
    Collider.ctor(self)
end

function BoxCollider:SetCpp()
    ---C++组件实例
    self.cpp = Cpp.BoxCollider()
end

return BoxCollider