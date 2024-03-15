//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "object.h"
#include "component.h"

namespace DivineBrush {
    class Component;
}

namespace DivineBrush {

    class GameObject : public Object {
    public:
        GameObject();

        GameObject(std::string name);

        ~GameObject() override = default;

    public:
        std::string GetName(){
           return this->name;
        }

        void SetName(std::string name){
            this->name = name;
        }

        Component *AddComponent(const std::string& componentName);

        Component *GetComponent(const std::string& componentName);

        virtual void start();

        virtual void update();

        virtual void fixedUpdate();

        virtual void lateUpdate();

        virtual void onEnable();

        virtual void onDisable();

        virtual void onDestroy();

    private:
        std::string name;
        std::unordered_map<std::string, std::vector<Component *>> component_map;
    };

} // DivineBrush

#endif //ENGINE_GAME_OBJECT_H
