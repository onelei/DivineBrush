//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include <unordered_map>
#include <string>
#include "Object.h"
#include "sol/sol.hpp"
#include <rttr/registration>

namespace DivineBrush {
    class GameObject;
}
namespace DivineBrush {

    class Component : public Object {

    public:
        Component() = default;

        ~Component() override = default;

        GameObject* GetGameObject();

        void SetGameObject(GameObject* gameObject);

        void SetLuaComponent(sol::table lua_component){
            this->luaComponent = lua_component;
        }

        void ExecuteLuaComponent(const char* function_name);

        virtual void OnAwake();

        virtual void OnUpdate();

        virtual void OnDestroy();

        virtual void OnPreprocessRender();

        virtual void OnPostprocessRender();

        virtual void OnEnable();

        virtual void OnDisable();

    protected:
        bool is_dirty = true;
        GameObject* gameObject = nullptr;
        sol::table luaComponent;
    };

} // DivineBrush

#endif //ENGINE_COMPONENT_H
