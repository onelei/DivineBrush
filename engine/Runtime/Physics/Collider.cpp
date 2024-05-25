//
// Created by onelei on 2024/4/26.
//

#include "rttr/registration"
#include "Physics.h"
#include "Collider.h"
#include "PhysicMaterial.h"

namespace DivineBrush {
    RTTR_REGISTRATION {
        rttr::registration::class_<Collider>("Collider")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Collider::Collider() {

    }

    Collider::~Collider() {

    }

    void Collider::SetTrigger(bool _isTrigger) {
        if (this->isTrigger == _isTrigger)
            return;
        this->isTrigger = _isTrigger;
        UnbindRigidBody();
        CreatePxShape();
        UpdateTriggerState();
        BindRigidBody();
    }

    void Collider::OnAwake() {
        Component::OnAwake();
        CreatePhysicMaterial();
        CreatePxShape();
        UpdateTriggerState();
        BindRigidBody();
    }

    void Collider::OnUpdate() {
        Component::OnUpdate();
    }

    void Collider::OnFixUpdate() {
        Component::OnFixUpdate();
    }

    void Collider::CreatePhysicMaterial() {
        if (physicMaterial == nullptr) {
            physicMaterial = new PhysicMaterial();
            physicMaterial->SetDynamicFriction(0.5f);
            physicMaterial->SetRestitution(0.5f);
            physicMaterial->SetStaticFriction(0.5f);
        }

        if (pxMaterial == nullptr) {
            pxMaterial = Physics::CreatePxMaterial(physicMaterial->GetStaticFriction(),
                                                   physicMaterial->GetDynamicFriction(),
                                                   physicMaterial->GetRestitution());
            pxMaterial->setRestitutionCombineMode(physx::PxCombineMode::eAVERAGE);
        }
    }

    void Collider::CreatePxShape() {

    }

    void Collider::UpdateTriggerState() {
        pxShape->setSimulationFilterData(physx::PxFilterData(isTrigger ? 1 : 0, 0, 0, 0));
        pxShape->userData = this->GetGameObject();
    }

    void Collider::BindRigidBody() {
        GetRigidBody()->BindCollider(this);
    }

    void Collider::UnbindRigidBody() {
        GetRigidBody()->UnbindCollider();
        pxShape = nullptr;
    }

    RigidBody *Collider::GetRigidBody() {
        if (rigidBody != nullptr) {
            return rigidBody;
        }
        rigidBody = GetGameObject()->GetComponent<RigidBody>();
        return rigidBody;
    }

} // DivineBrush