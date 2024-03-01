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
        GameObject() = default;

        GameObject(std::string name);

        ~GameObject() override = default;

    public:
        std::string getName(){
           return this->_name;
        }

        void setName(std::string name){
            this->_name = name;
        }

        Component *addComponent(std::string component_name);

        Component *getComponent(std::string component_name);

        virtual void start();

        virtual void update();

        virtual void fixedUpdate();

        virtual void lateUpdate();

        virtual void onEnable();

        virtual void onDisable();

        virtual void onDestroy();

    private:
        std::string _name;
        std::unordered_map<std::string, std::vector<Component *>> _component_map;
    };

} // DivineBrush

#endif //ENGINE_GAME_OBJECT_H
