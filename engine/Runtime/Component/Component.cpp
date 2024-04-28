//
// Created by onelei on 2024/2/29.
//

#include "Component.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    GameObject *Component::GetGameObject() {
        return this->gameObject;
    }

    void Component::SetGameObject(GameObject *gameObject) {
        this->gameObject = gameObject;
    }

    void Component::OnAwake() {
        ExecuteLuaComponent("OnAwake");
    }

    void Component::OnUpdate() {
        ExecuteLuaComponent("OnUpdate");
    }

    void Component::OnFixUpdate() {
        ExecuteLuaComponent("OnFixUpdate");
    }

    void Component::OnDestroy() {
        ExecuteLuaComponent("OnDestroy");
    }

    void Component::OnPreprocessRender() {
        ExecuteLuaComponent("OnPreprocessRender");
    }

    void Component::OnPostprocessRender() {
        ExecuteLuaComponent("OnPostprocessRender");
    }

    void Component::OnEnable() {
        ExecuteLuaComponent("OnEnable");
    }

    void Component::OnDisable() {
        ExecuteLuaComponent("OnDisable");
    }

    void Component::OnTriggerEnter(GameObject *other) {
        ExecuteLuaComponent("OnTriggerEnter", other);
    }

    void Component::OnTriggerStay(GameObject *other) {
        ExecuteLuaComponent("OnTriggerStay", other);
    }

    void Component::OnTriggerExit(GameObject *other) {
        ExecuteLuaComponent("OnTriggerExit", other);
    }

    void Component::ExecuteLuaComponent(const char *function_name, GameObject *other) {
        if (!luaComponent.valid()) {
            return;
        }
        auto function_awake = luaComponent[function_name];
        if (!function_awake.valid()) {
            return;
        }
        auto result = function_awake(luaComponent, other);
        if (!result.valid()) {
            sol::error err = result;
            //type t = type::get(this);
            //std::string component_type_name = t.get_name().to_string();
            //DEBUG_LOG_ERROR("\n---- RUN LUA_FUNCTION ERROR ----\nComponent call Awake error,type:{}\n{}\n------------------------",component_type_name,err.what());
        }
    }

} // DivineBrush