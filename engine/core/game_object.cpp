//
// Created by onelei on 2024/2/29.
//

#include "game_object.h"
#include "rttr/registration.h"

using namespace rttr;
namespace DivineBrush {
    GameObject::GameObject(std::string name) {
        this->setName(name);
    }

    Component *GameObject::addComponent(std::string component_name) {
        type t = type::get_by_name(component_name);
        variant var = t.create();
        Component *component = var.get_value<Component *>();
        component->setGameObject(this);
        return component;
    }

    Component *GameObject::getComponent(std::string component_name) {
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