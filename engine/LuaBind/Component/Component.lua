---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/4/1 16:48
---
---@class Component:BaseCpp
local Component = class("Component", BaseCpp)

function Component:ctor()
    ---@type table[string,Component[]]
    self.components = {}
    ---@type GameObject
    self.gameObject = nil
    BaseCpp.ctor(self)
    self:GetCpp():SetLuaComponent(self)
end

function Component:SetCpp(...)
    ---C++组件实例
    self.cpp = Cpp.Component()
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