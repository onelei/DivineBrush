//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include <unordered_map>
#include <string>
#include "object.h"

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

        virtual void Awake();

        virtual void Update();

        virtual void Destroy();

    private:
        GameObject* gameObject = nullptr;
    };

} // DivineBrush

#endif //ENGINE_COMPONENT_H
