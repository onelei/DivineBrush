//
// Created by onelei on 2024/4/28.
//

#include "RigidBody.h"
#include "rttr/registration.h"
#include "../Component/GameObject.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<RigidBody>("RigidBody")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    RigidBody::RigidBody() {

    }

    RigidBody::~RigidBody() {

    }

    void RigidBody::OnAwake() {
        Component::OnAwake();
        auto component = gameObject->GetComponent("Collider");
        auto collider = dynamic_cast<Collider *>(component);
        BindCollider(collider);
    }

    void RigidBody::BindCollider(Collider *collider) {
        if (collider == nullptr) {
            return;
        }
        auto pxShape = collider->GetPxShape();
        pxRigidActor->attachShape(*pxShape);
        pxShape->release();
    }

    void RigidBody::UnbindCollider(Collider *collider) {
        if (collider == nullptr) {
            return;
        }
        auto pxShape = collider->GetPxShape();
        pxRigidActor->detachShape(*pxShape);
    }

    void RigidBody::SetRigidActor(physx::PxRigidActor *rigidActor) {
        this->pxRigidActor = rigidActor;
    }

    physx::PxRigidActor *RigidBody::GetRigidActor() {
        return pxRigidActor;
    }
} // DivineBrush