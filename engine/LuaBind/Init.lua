---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by onelei.
--- DateTime: 2024/4/1 16:51
---
require("Base.Function")
BaseCpp = require("Base.BaseCpp")
GameObject = require("Component.GameObject")
Component = require("Component.Component")
Transform = require("Component.Transform")
---Physics
RaycastHit = require("Physics.RaycastHit")
Collider = require("Physics.Collider")
Physics = require("Physics.Physics")
RigidBody = require("Physics.RigidBody")
BoxCollider = require("Physics.BoxCollider")
SphereCollider = require("Physics.SphereCollider")
PhysicMaterial = require("Physics.PhysicMaterial")
---Light
Environment = require("Lighting.Environment")
Light = require("Lighting.Light")
---Render
Material = require("Render.Material")
MeshFilter = require("Render.MeshFilter")
MeshRenderer = require("Render.MeshRenderer")
SkinnedMeshRenderer = require("Render.SkinnedMeshRenderer")
---Animation
AnimationClip = require("Animation.AnimationClip")
Animation = require("Animation.Animation")

function main()
    print("Hello World!")
    local gameObject = GameObject.new("Lua-GameObject")
    print("gameObject:" .. tostring(gameObject))
    gameObject:SetName("Lua-GameObject2")
    print("gameObject name:" .. gameObject:GetName())

    ---Physics
    ---@type GameObject
    local ground = GameObject.new("ground")
    ---@type Transform
    print("2")
    local groundTransform = ground:GetTransform()
    print("1")
    groundTransform:SetPosition(Cpp.Vector3(0, -2, 0))
    ground:AddComponent(RigidBody):SetDynamic(false)
    --TODO Collider::BindRigidBody() 会报错, 所以后添加 BoxCollider
    ground:AddComponent(BoxCollider):SetTrigger(false)
    ---@type GameObject
    local sphere = GameObject.new("sphere")
    ---@type Transform
    local sphereTransform = sphere:GetTransform()
    sphereTransform:SetPosition(Cpp.Vector3(0, 2, 0))
    sphere:AddComponent(RigidBody):SetDynamic(true)
    sphere:AddComponent(SphereCollider):SetTrigger(false)
    print("6")

    ---@type Material
    --local material = Material.new()
    --material:Parse("material/light.mat")
    --material:SetUniformVector3("u_view_pos",camera_position)
    --设置物体反射度、高光强度
    --material:SetUniformFloat("u_specular_highlight_shininess",32.0)

    ---创建灯光
    local environment = Environment.new()
    environment:SetAmbientColor(Cpp.Vector3(1.0, 1.0, 1.0))
    environment:SetAmbientIntensity(0.3)
    print("Environment")
    ---创建DirectionalLight
    local directionalLight1 = GameObject.new("directionalLight1")
    directionalLight1:GetTransform():SetRotation(Cpp.Vector3(0, 60, 0))
    ---@type Light
    local light1 = directionalLight1:AddComponent(Light)
    light1:SetColor(Cpp.Vector3(1.0, 1.0, 1.0))
    light1:SetIntensity(1.0)
    print("directionalLight1")
    ---创建DirectionalLight
    local directionalLight2 = GameObject.new("directionalLight1")
    directionalLight2:GetTransform():SetRotation(Cpp.Vector3(240, 0, 0))
    ---@type Light
    local light2 = directionalLight2:AddComponent(Light)
    light2:SetColor(Cpp.Vector3(1.0, 1.0, 1.0))
    light2:SetIntensity(1.0)
    print("directionalLight2")
    ---创建PointLight
    local pointLight1 = GameObject.new("pointLight1")
    pointLight1:GetTransform():SetPosition(Cpp.Vector3(-2, 0, 5))
    ---@type Light
    local light3 = pointLight1:AddComponent(Light)
    light3:SetColor(Cpp.Vector3(1.0, 0.0, 0.0))
    light3:SetIntensity(1.0)
    light3:SetAttenuationConst(1.0)
    light3:SetAttenuationLinear(0.35)
    light3:SetAttenuationQuadratic(0.44)
    print("PointLight1")
    ---创建PointLight
    local pointLight2 = GameObject.new("pointLight2")
    pointLight2:GetTransform():SetPosition(Cpp.Vector3(2, 0, 5))
    ---@type Light
    local light4 = pointLight2:AddComponent(Light)
    light4:SetColor(Cpp.Vector3(0.0, 1.0, 0.0))
    light4:SetIntensity(1.0)
    light4:SetAttenuationConst(1.0)
    light4:SetAttenuationLinear(0.35)
    light4:SetAttenuationQuadratic(0.44)
    print("PointLight2")


    ---创建骨骼蒙皮动画
    --local skeletonObj = GameObject.new("skeleton")
    --skeletonObj:GetTransform():SetPosition(Cpp.Vector3(0, -1, 0))
    --skeletonObj:GetTransform():SetRotation(Cpp.Vector3(-90, 0, 0))
    -----@type Animation
    --local animation = skeletonObj:AddComponent(Animation)
    --animation:LoadFromFile("animation/fbx_extra_bip001_bip001_take_001_baselayer.skeleton_anim", "idle")
    --local mesh_filter = skeletonObj:AddComponent(MeshFilter)
    --mesh_filter:LoadMesh("model/fbx_extra_jiulian.mesh")
    -----加载Mesh
    --mesh_filter:LoadWeight("model/fbx_extra_jiulian.weight")
    -----加载权重文件
    -----手动创建Material
    --local skeletonMaterial = Material.new()---设置材质
    --skeletonMaterial:Parse("material/fbx_extra_jiulian.mat")
    --print("skeleton")
    -----挂上 MeshRenderer 组件
    -----@type SkinnedMeshRenderer
    --local skinned_mesh_renderer = skeletonObj:AddComponent(SkinnedMeshRenderer)
    --skinned_mesh_renderer:SetMaterial(skeletonMaterial)
    -----播放动画
    --skeletonObj:GetComponent(Animation):Play("idle")
    --print("idle")
end