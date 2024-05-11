//
// Created by onelei on 2024/4/28.
//

#include "RigidBody.h"
#include "rttr/registration.h"
#include "Physics.h"

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
        // Component::OnAwake();
        Component::OnAwake();
        CreatePxRigidActor();
    }

    void RigidBody::OnFixUpdate() {
        Component::OnFixUpdate();
        if (isDynamic) {
            auto pose = pxRigidActor->getGlobalPose();
            auto transform = gameObject->GetTransform();
            transform->SetPosition(glm::vec3(pose.p.x, pose.p.y, pose.p.z));
        }
    }

    void RigidBody::BindCollider(Collider *_collider) {
        if (_collider == nullptr) {
            return;
        }
        collider = _collider;
        auto pxShape = collider->GetPxShape();
        pxRigidActor->attachShape(*pxShape);
        pxShape->release();
    }

    void RigidBody::UnbindCollider() {
        if (collider == nullptr || pxRigidActor == nullptr) {
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

    void RigidBody::SetEnableCCD(bool _enableCCD) {
        enableCCD = _enableCCD;
        if (isDynamic) {
            auto pxRigidDynamic = dynamic_cast<physx::PxRigidDynamic *>(pxRigidActor);
            pxRigidDynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, enableCCD);
        }
    }

    bool RigidBody::GetEnableCCD() const {
        return enableCCD;
    }

    void RigidBody::SetDynamic(bool _isDynamic) {
        if (isDynamic == _isDynamic)
            return;
        isDynamic = _isDynamic;
        CreatePxRigidActor();
    }

    bool RigidBody::GetDynamic() const {
        return isDynamic;
    }

    void RigidBody::CreatePxRigidActor() {
        UnbindCollider();
        auto transform = gameObject->GetTransform();
        if (isDynamic) {
            auto pxRigidDynamic = Physics::CreatePxRigidDynamic(transform->GetPosition(), gameObject->GetName());
            pxRigidActor = dynamic_cast<physx::PxRigidActor *>(pxRigidDynamic);
        } else {
            auto pxRigidStatic = Physics::CreatePxRigidStatic(transform->GetPosition(), gameObject->GetName());
            pxRigidActor = dynamic_cast<physx::PxRigidActor *>(pxRigidStatic);
        }
        auto component = gameObject->GetComponent("Collider");
        auto _collider = dynamic_cast<Collider *>(component);
        BindCollider(_collider);
    }

} // DivineBrush