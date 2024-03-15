//
// Created by onelei on 2024/2/29.
//

#include "game_object.h"
#include "rttr/registration.h"

using namespace rttr;
namespace DivineBrush {

    GameObject::GameObject() {
        this->SetName("GameObject");
    }

    GameObject::GameObject(std::string name) {
        this->SetName(name);
    }

    Component *GameObject::AddComponent(const std::string &componentName) {
        type t = type::get_by_name(componentName);
        variant var = t.create();
        Component *component = var.get_value<Component *>();
        component->SetGameObject(this);
        if (component_map.find(componentName) == component_map.end()) {
            std::vector<Component *> componentVec;
            componentVec.push_back(component);
            component_map[componentName] = componentVec;
        } else {
            component_map[componentName].push_back(component);
        }
        return component;
    }

    Component *GameObject::GetComponent(const std::string &componentName) {
        if (component_map.find(componentName) != component_map.end()) {
            return component_map[componentName][0];
        }
        return nullptr;
    }

    void GameObject::start() {

    }

    void GameObject::update() {

    }

    void GameObject::fixedUpdate() {

    }

    void GameObject::lateUpdate() {

    }

    void GameObject::onEnable() {

    }

    void GameObject::onDisable() {

    }

    void GameObject::onDestroy() {

    }
} // DivineBrush