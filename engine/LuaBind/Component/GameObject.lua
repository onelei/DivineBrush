---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/4/1 16:24
---
---@class GameObject
local GameObject = class("GameObject")

function GameObject:ctor(name)
    ---@type table[string,Component[]]
    self.componentMap = {}
    self.cpp = Cpp.GameObject(name)
end

function GameObject:GetCpp()
    return self.cpp
end

function GameObject:GetName()
    return self:GetCpp():GetName()
end

--- SetName
--- @param name string
function GameObject:SetName(name)
    self:GetCpp():SetName(name)
end

--- AddComponent
--- @param component_type string 组件类型
--- @return Component 组件实例
function GameObject:AddComponent(component_type)
    ---@type Component
    local component = component_type.new()
    if self.componentMap[component_type] == nil then
        self.componentMap[component_type] = {}
    end
    table.insert(self.componentMap[component_type], component)
    component:SetGameObject(self)
    return component
end

--- GetComponent
--- @param component_type string 组件类型
--- @return Component 组件实例
function GameObject:GetComponent(component_type)
    local components = self.componentMap[component_type]
    if components and #components > 0 then
        return components[1]
    end
    return nil
end

function GameObject:RemoveComponent(component)
    for i, v in ipairs(self.components) do
        if v == component then
            table.remove(self.components, i)
            break
        end
    end
end

function GameObject:Update()
    for i, v in ipairs(self.components) do
        v:Update()
    end
end

return GameObject