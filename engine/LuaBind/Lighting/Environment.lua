﻿---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/5/18 16:23
---
---@class Environment:BaseCpp
local Environment = class("Environment", BaseCpp)

function Environment:ctor()
    BaseCpp.ctor(self)
end

function Environment:SetCpp(...)
    ---C++组件实例
    self.cpp = Cpp.Environment()
end

function Environment:SetAmbientColor(color)
    self:GetCpp():SetAmbientColor(color)
end

function Environment:SetAmbientIntensity(intensity)
    self:GetCpp():SetAmbientIntensity(intensity)
end

function Environment:GetAmbientColor()
    return self:GetCpp():GetAmbientColor()
end

function Environment:GetAmbientIntensity()
    return self:GetCpp():GetAmbientIntensity()
end

return Environment