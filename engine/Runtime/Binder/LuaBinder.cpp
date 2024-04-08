//
// Created by onelei on 2024/4/1.
//

#include "LuaBinder.h"
#include "../Component/GameObject.h"
#include "../Component/Component.h"

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

        //绑定 GameObject
        cpp_ns_table.new_usertype<DivineBrush::GameObject>("GameObject", sol::call_constructor,
                                                           sol::constructors<DivineBrush::GameObject(const char *)>(),
                                                           "AddComponent", &DivineBrush::GameObject::AddComponent,
                                                           "GetName", &DivineBrush::GameObject::GetName,
                                                           "SetName", &DivineBrush::GameObject::SetName
        );

        //绑定 Component
        cpp_ns_table.new_usertype<DivineBrush::Component>("Component", sol::call_constructor,
                                                          sol::constructors<DivineBrush::Component()>(),
                                                          "OnAwake", &DivineBrush::Component::OnAwake,
                                                          "OnUpdate", &DivineBrush::Component::OnUpdate,
                                                          "GetGameObject", &DivineBrush::Component::GetGameObject,
                                                          "SetGameObject", &DivineBrush::Component::SetGameObject
                //"set_lua_component_instance",&Component::set_lua_component_instance
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
