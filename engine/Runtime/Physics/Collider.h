//
// Created by onelei on 2024/4/26.
//

#ifndef ENGINE_COLLIDER_H
#define ENGINE_COLLIDER_H

#include "PxPhysicsAPI.h"
#include "../Component/Component.h"
#include "RigidBody.h"

namespace DivineBrush {
    class RigidBody;

    class PhysicMaterial;

    class Collider : public Component {
    public:
        Collider();

        ~Collider();

        physx::PxShape *GetPxShape() {
            return pxShape;
        }

        void SetTrigger(bool isTrigger);

        void OnAwake() override;

        void OnUpdate() override;

        void OnFixUpdate() override;

        virtual void CreatePhysicMaterial();

        virtual void CreatePxShape();

        virtual void UpdateTriggerState();

        virtual void BindRigidBody();

        virtual void UnbindRigidBody();

        RigidBody *GetRigidBody();

    protected:
        physx::PxShape *pxShape = nullptr;
        physx::PxMaterial *pxMaterial = nullptr;
        RigidBody *rigidBody = nullptr;
        bool isTrigger = false;

    private:
        PhysicMaterial *physicMaterial = nullptr;
    RTTR_ENABLE(Component);
    };

} // DivineBrush

#endif //ENGINE_COLLIDER_H
