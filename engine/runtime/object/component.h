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

        virtual void OnAwake();

        virtual void OnUpdate();

        virtual void OnDestroy();

        virtual void OnPreprocessRender();

        virtual void OnPostprocessRender();

        virtual void OnEnable();

        virtual void OnDisable();

    private:
        GameObject* gameObject = nullptr;
        bool is_dirty = true;
    };

} // DivineBrush

#endif //ENGINE_COMPONENT_H
