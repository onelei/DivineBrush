//
// Created by onelei on 2024/4/28.
//

#include "RaycastHit.h"

namespace DivineBrush {
    glm::vec3 RaycastHit::GetPosition() {
        return position;
    }

    GameObject *RaycastHit::GetGameObject() {
        return gameObject;
    }

    void RaycastHit::SetPosition(glm::vec3 pos) {
        this->position = pos;
    }

    void RaycastHit::SetGameObject(GameObject *gameObj) {
        this->gameObject = gameObj;
    }
} // DivineBrush