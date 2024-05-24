//
// Created by onelei on 2024/4/1.
//

#include "LuaBinder.h"
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include "../Component/GameObject.h"
#include "../Component/Component.h"
#include "../Physics/Physics.h"
#include "../Physics/PhysicMaterial.h"
#include "../Physics/Rigidbody.h"
#include "../Physics/BoxCollider.h"
#include "../Physics/SphereCollider.h"
#include "../Physics/RaycastHit.h"
#include "../Physics/Collider.h"
#include "../Lighting/Environment.h"
#include "../Lighting/Light.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationClip.h"
#include "../Render/MeshFilter.h"
#include "../Render/MeshRenderer.h"
#include "../Render/Material.h"
#include "../Render/SkinnedMeshRenderer.h"

namespace DivineBrush {
    void LuaBinder::Init() {
        solState.open_libraries(sol::lib::base,
                                sol::lib::package,
                                sol::lib::coroutine,
                                sol::lib::string,
                                sol::lib::table,
                                sol::lib::math,
                                sol::lib::io,
                                sol::lib::os,
                                sol::lib::debug,
                                sol::lib::bit32,
                                sol::lib::utf8
        );

        auto cpp_ns_table = solState["Cpp"].get_or_create<sol::table>();

        cpp_ns_table.new_usertype<glm::vec3>(
                "Vector3", sol::call_constructor,
                sol::constructors<glm::vec3(const float &, const float &, const float &)>(),
                "x", &glm::vec3::x,
                "y", &glm::vec3::y,
                "z", &glm::vec3::z,
                "r", &glm::vec3::r,
                "g", &glm::vec3::g,
                "b", &glm::vec3::b,
                sol::meta_function::to_string, [](const glm::vec3 *vec) -> std::string { return glm::to_string(*vec); },
                sol::meta_function::addition,
                [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) { return (*vec_a) + (*vec_b); },
                sol::meta_function::subtraction,
                [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) { return (*vec_a) - (*vec_b); },
                sol::meta_function::multiplication, [](const glm::vec3 *vec, const float a) { return (*vec) * a; },
                sol::meta_function::division, [](const glm::vec3 *vec, const float a) { return (*vec) / a; },
                //sol::meta_function::unary_minus, [](const glm::vec3 *vec) { return (*vec) * -1; },
                sol::meta_function::equal_to,
                [](const glm::vec3 *vec_a, const glm::vec3 *vec_b) { return (*vec_a) == (*vec_b); }
        );

        //绑定GameObject
        cpp_ns_table.new_usertype<DivineBrush::GameObject>(
                "GameObject", sol::call_constructor,
                sol::constructors<DivineBrush::GameObject(const char *)>(),
                "GetTransform", &DivineBrush::GameObject::GetTransform,
                "AddComponentByLua", &DivineBrush::GameObject::AddComponentByLua,
                "GetName", &DivineBrush::GameObject::GetName,
                "SetName", &DivineBrush::GameObject::SetName
        );

        //绑定Transform
        cpp_ns_table.new_usertype<DivineBrush::Transform>(
                "Transform", sol::call_constructor,
                sol::constructors<DivineBrush::Transform()>(),
                sol::base_classes, sol::bases<Component>(),
                "GetPosition", &DivineBrush::Transform::GetPosition,
                "SetPosition", &DivineBrush::Transform::SetPosition,
                "GetRotation", &DivineBrush::Transform::GetRotation,
                "SetRotation", &DivineBrush::Transform::SetRotation,
                "GetScale", &DivineBrush::Transform::GetScale,
                "SetScale", &DivineBrush::Transform::SetScale
        );

        //绑定Component
        cpp_ns_table.new_usertype<DivineBrush::Component>(
                "Component", sol::call_constructor,
                sol::constructors<DivineBrush::Component()>(),
                "SetLuaComponent", &DivineBrush::Component::SetLuaComponent,
                "OnAwake", &DivineBrush::Component::OnAwake,
                "OnUpdate", &DivineBrush::Component::OnUpdate,
                "GetGameObject", &DivineBrush::Component::GetGameObject,
                "SetGameObject", &DivineBrush::Component::SetGameObject
        );

        //绑定Environment
        cpp_ns_table.new_usertype<DivineBrush::Environment>(
                "Environment", sol::call_constructor,
                sol::constructors<DivineBrush::Environment()>(),
                "SetAmbientColor", &DivineBrush::Environment::SetAmbientColor,
                "SetAmbientIntensity", &DivineBrush::Environment::SetAmbientIntensity,
                "GetAmbientColor", &DivineBrush::Environment::GetAmbientColor,
                "GetAmbientIntensity", &DivineBrush::Environment::GetAmbientIntensity
        );

        //绑定Light
        cpp_ns_table.new_usertype<DivineBrush::Light>(
                "Light", sol::call_constructor,
                sol::constructors<DivineBrush::Light()>(),
                sol::base_classes, sol::bases<Component>(),
                "SetLightType", &DivineBrush::Light::SetLightType,
                "SetColor", &DivineBrush::Light::SetColor,
                "GetColor", &DivineBrush::Light::GetColor,
                "SetIntensity", &DivineBrush::Light::SetIntensity,
                "GetIntensity", &DivineBrush::Light::GetIntensity,
                "SetAttenuationConst", &DivineBrush::Light::SetAttenuationConst,
                "GetAttenuationConst", &DivineBrush::Light::GetAttenuationConst,
                "SetAttenuationLinear", &DivineBrush::Light::SetAttenuationLinear,
                "GetAttenuationLinear", &DivineBrush::Light::GetAttenuationLinear,
                "SetAttenuationQuadratic", &DivineBrush::Light::SetAttenuationQuadratic,
                "GetAttenuationQuadratic", &DivineBrush::Light::GetAttenuationQuadratic
        );


        //绑定Physics
        cpp_ns_table.new_usertype<DivineBrush::Physics>(
                "Physics", sol::call_constructor,
                sol::constructors<DivineBrush::Physics()>(),
                "CreatPxScene", &DivineBrush::Physics::CreatPxScene,
                "CreatePxRigidDynamic", &DivineBrush::Physics::CreatePxRigidDynamic,
                "CreatePxRigidStatic", &DivineBrush::Physics::CreatePxRigidStatic,
                "CreatePxMaterial", &DivineBrush::Physics::CreatePxMaterial,
                "CreateSphereShape", &DivineBrush::Physics::CreateSphereShape,
                "CreateBoxShape", &DivineBrush::Physics::CreateBoxShape,
                "RaycastSingle", &DivineBrush::Physics::RaycastSingle,
                "GetEnableCCD", &DivineBrush::Physics::GetEnableCCD,
                "SetEnableCCD", &DivineBrush::Physics::SetEnableCCD
        );

        //绑定PhysicMaterial
        cpp_ns_table.new_usertype<DivineBrush::PhysicMaterial>(
                "PhysicMaterial", sol::call_constructor,
                sol::constructors<DivineBrush::PhysicMaterial()>(),
                "SetDynamicFriction", &DivineBrush::PhysicMaterial::SetDynamicFriction,
                "SetStaticFriction", &DivineBrush::PhysicMaterial::SetStaticFriction,
                "SetRestitution", &DivineBrush::PhysicMaterial::SetRestitution,
                "GetDynamicFriction", &DivineBrush::PhysicMaterial::GetDynamicFriction,
                "GetStaticFriction", &DivineBrush::PhysicMaterial::GetStaticFriction,
                "GetRestitution", &DivineBrush::PhysicMaterial::GetRestitution
        );

        //绑定Collider
        cpp_ns_table.new_usertype<DivineBrush::Collider>(
                "Collider", sol::call_constructor,
                sol::constructors<DivineBrush::Collider()>(),
                sol::base_classes, sol::bases<Component>(),
                "GetPxShape", &DivineBrush::Collider::GetPxShape,
                "SetTrigger", &DivineBrush::Collider::SetTrigger,
                "CreatePhysicMaterial", &DivineBrush::Collider::CreatePhysicMaterial,
                "CreatePxShape", &DivineBrush::Collider::CreatePxShape,
                "GetRigidBody", &DivineBrush::Collider::GetRigidBody
        );

        //绑定BoxCollider
        cpp_ns_table.new_usertype<DivineBrush::BoxCollider>(
                "BoxCollider", sol::call_constructor,
                sol::constructors<DivineBrush::BoxCollider()>(),
                sol::base_classes, sol::bases<Collider, Component>()
        );

        //绑定SphereCollider
        cpp_ns_table.new_usertype<DivineBrush::SphereCollider>(
                "SphereCollider", sol::call_constructor,
                sol::constructors<DivineBrush::SphereCollider()>(),
                sol::base_classes, sol::bases<Collider, Component>()
        );

        //绑定RaycastHit
        cpp_ns_table.new_usertype<DivineBrush::RaycastHit>(
                "RaycastHit", sol::call_constructor,
                sol::constructors<DivineBrush::RaycastHit()>(),
                "GetPosition", &DivineBrush::RaycastHit::GetPosition,
                "GetGameObject", &DivineBrush::RaycastHit::GetGameObject
        );

        //绑定RigidBody
        cpp_ns_table.new_usertype<DivineBrush::RigidBody>(
                "RigidBody", sol::call_constructor,
                sol::constructors<DivineBrush::RigidBody()>(),
                sol::base_classes, sol::bases<Component>(),
                "SetEnableCCD", &DivineBrush::RigidBody::SetEnableCCD,
                "GetEnableCCD", &DivineBrush::RigidBody::GetEnableCCD,
                "SetDynamic", &DivineBrush::RigidBody::SetDynamic,
                "GetDynamic", &DivineBrush::RigidBody::GetDynamic
        );

        //绑定AnimationClip
        cpp_ns_table.new_usertype<DivineBrush::AnimationClip>(
                "AnimationClip", sol::call_constructor,
                sol::constructors<DivineBrush::AnimationClip()>(),
                "LoadFromFile", &DivineBrush::AnimationClip::LoadFromFile,
                "GetCurrentFrameBoneMat4", &DivineBrush::AnimationClip::GetCurrentFrameBoneMat4,
                "GetCurrentFrameNormalBoneMat3", &DivineBrush::AnimationClip::GetCurrentFrameNormalBoneMat3,
                "Play", &DivineBrush::AnimationClip::Play,
                "Stop", &DivineBrush::AnimationClip::Stop
        );

        //绑定Animation
        cpp_ns_table.new_usertype<DivineBrush::Animation>(
                "Animation", sol::call_constructor,
                sol::constructors<DivineBrush::Animation()>(),
                sol::base_classes, sol::bases<Component>(),
                "LoadFromFile", &DivineBrush::Animation::LoadFromFile,
                "GetAnimationClip", &DivineBrush::Animation::GetAnimationClip,
                "Play", &DivineBrush::Animation::Play,
                "Stop", &DivineBrush::Animation::Stop
        );

        //绑定Material
        cpp_ns_table.new_usertype<DivineBrush::Material>(
                "Material", sol::call_constructor,
                sol::constructors<DivineBrush::Material()>(),
                "Parse", &DivineBrush::Material::Parse,
                "SetUniformInt", &DivineBrush::Material::SetUniformInt,
                "SetUniformFloat", &DivineBrush::Material::SetUniformFloat,
                "SetUniformVector3", &DivineBrush::Material::SetUniformVector3,
                "SetTexture", &DivineBrush::Material::SetTexture,
                "GetShader", &DivineBrush::Material::GetShader,
                "GetTextures", &DivineBrush::Material::GetTextures
        );

        //绑定MeshFilter
        cpp_ns_table.new_usertype<DivineBrush::MeshFilter>(
                "MeshFilter", sol::call_constructor,
                sol::constructors<DivineBrush::MeshFilter()>(),
                sol::base_classes, sol::bases<Component>(),
                "LoadMesh", &DivineBrush::MeshFilter::LoadMesh,
                "CreateMesh", &DivineBrush::MeshFilter::CreateMeshLua,
                "GetMesh", &DivineBrush::MeshFilter::GetMesh,
                "GetSkinMesh", &DivineBrush::MeshFilter::GetSkinMesh,
                "GetMeshName", &DivineBrush::MeshFilter::GetMeshName,
                "SetBoneInfo", &DivineBrush::MeshFilter::SetBoneInfo,
                "LoadWeight", &DivineBrush::MeshFilter::LoadWeight
        );

        //绑定MeshRenderer
        cpp_ns_table.new_usertype<DivineBrush::MeshRenderer>(
                "MeshRenderer", sol::call_constructor,
                sol::constructors<DivineBrush::MeshRenderer()>(),
                sol::base_classes, sol::bases<Component>(),
                "SetMaterial", &DivineBrush::MeshRenderer::SetMaterial,
                "GetMaterial", &DivineBrush::MeshRenderer::GetMaterial,
                "SetMeshFilter", &DivineBrush::MeshRenderer::SetMeshFilter,
                "GetMeshFilter", &DivineBrush::MeshRenderer::GetMeshFilter
        );

        //绑定SkinnedMeshRenderer
        cpp_ns_table.new_usertype<DivineBrush::SkinnedMeshRenderer>(
                "SkinMeshRenderer", sol::call_constructor,
                sol::constructors<DivineBrush::SkinnedMeshRenderer()>(),
                sol::base_classes, sol::bases<MeshRenderer, Component>(),
                "OnUpdate", &DivineBrush::SkinnedMeshRenderer::OnUpdate
        );


        //设置lua搜索目录
        sol::table package_table = solState["package"];
        std::string path = package_table["path"];
        path.append(";../LuaBind/?.lua;");
        path.append(";../samples/?.lua;");
        package_table["path"] = path;

        //执行lua
        auto result = solState.script_file("../LuaBind/Init.lua");
        if (!result.valid()) {
            sol::error err = result;
            std::cerr << err.what() << std::endl;
        }

        //调用lua main()
        auto main_function = solState["main"];
        result = main_function();
    }
}
