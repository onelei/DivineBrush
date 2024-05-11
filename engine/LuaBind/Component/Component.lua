---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/4/1 16:48
---
---@class Component
local Component = class("Component")

function Component:ctor()
    ---@type table[string,Component[]]
    self.components = {}
    ---@type GameObject
    self.gameObject = nil
    self:SetCpp()
    self:GetCpp():SetLuaComponent(self)
end

function Component:SetCpp()
    ---C++组件实例
    self.cpp = Cpp.Component()
end

--- GetCpp
function Component:GetCpp()
    return self.cpp
end

--- OnAwake
function Component:OnAwake()
    ---print("Component:OnAwake")
end

function Component:OnUpdate()
    ---print("Component:OnUpdate")
end

function Component:OnPreRender()
end

function Component:OnPostRender()
end

function Component:OnDisable()
end

function Component:OnEnable()
end

function Component:GetGameObject()
    return self.gameObject
end

--- SetGameObject
--- @param gameObject GameObject
function Component:SetGameObject(gameObject)
    self.gameObject = gameObject
    gameObject:GetCpp():AddComponentByLua(self.__cname, self.cpp)
    self.cpp:OnAwake()
end

return Component