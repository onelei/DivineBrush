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

        void OnFixUpdate() override;

        virtual void BindCollider(Collider *collider);

        virtual void UnbindCollider(Collider *collider);

        void SetRigidActor(physx::PxRigidActor *pxRigidActor);

        physx::PxRigidActor *GetRigidActor();

        void SetEnableCCD(bool enableCCD);

        bool GetEnableCCD() const;

        void SetDynamic(bool isDynamic);

        bool GetDynamic() const;

    private:
        physx::PxRigidActor *pxRigidActor = nullptr;
        bool enableCCD = false;
        bool isDynamic = false;
    };

} // DivineBrush

#endif //ENGINE_RIGIDBODY_H
