//
// Created by onelei on 2024/4/28.
//

#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "../Component/Component.h"
#include "Collider.h"

namespace DivineBrush {
    class Collider;

    class RigidBody : public Component {
    public:
        RigidBody();

        ~RigidBody();

        void OnAwake() override;

        virtual void BindCollider(Collider *collider);

        virtual void UnbindCollider(Collider *collider);

        void SetRigidActor(physx::PxRigidActor *pxRigidActor);

        physx::PxRigidActor *GetRigidActor();

    private:
        physx::PxRigidActor *pxRigidActor = nullptr;
    };

} // DivineBrush

#endif //ENGINE_RIGIDBODY_H
