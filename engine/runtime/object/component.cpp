//
// Created by onelei on 2024/2/29.
//

#include "component.h"

namespace DivineBrush {
    GameObject * Component::GetGameObject() {
        return this->gameObject;
    }

    void Component::SetGameObject(GameObject *gameObject) {
        this->gameObject = gameObject;
    }

    void Component::OnAwake() {

    }

    void Component::OnUpdate() {

    }

    void Component::OnDestroy() {

    }

    void Component::OnPreprocessRender() {

    }

    void Component::OnPostprocessRender() {

    }

    void Component::OnEnable() {

    }

    void Component::OnDisable() {

    }

} // DivineBrush