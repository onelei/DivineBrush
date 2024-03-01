//
// Created by onelei on 2024/2/29.
//

#include "component.h"

namespace DivineBrush {
    GameObject * Component::getGameObject() {
        return this->_gameObject;
    }

    void Component::setGameObject(GameObject *gameObject) {
        this->_gameObject = gameObject;
    }
} // DivineBrush