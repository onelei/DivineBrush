//
// Created by onelei on 2024/4/28.
//

#ifndef ENGINE_RAYCASTHIT_H
#define ENGINE_RAYCASTHIT_H

#include <glm/glm.hpp>
#include "../Component/GameObject.h"

namespace DivineBrush {

    class RaycastHit {
    public:
        glm::vec3 GetPosition();

        GameObject *GetGameObject();

        void SetPosition(glm::vec3 vec3);

        void SetGameObject(GameObject *pGameObject);

    private:
        glm::vec3 position;
        GameObject *gameObject;
    };

} // DivineBrush

#endif //ENGINE_RAYCASTHIT_H
