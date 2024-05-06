//
// Created by onelei on 2024/5/6.
//

#include "SphereCollider.h"
#include "rttr/registration.h"
#include "Physics.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<SphereCollider>("SphereCollider")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    SphereCollider::SphereCollider() {

    }

    SphereCollider::~SphereCollider() {

    }

    void SphereCollider::CreatePxShape() {
        Collider::CreatePxShape();
        pxShape = Physics::CreateSphereShape(radius, pxMaterial);
    }

    void SphereCollider::SetRadius(float _radius) {
        radius = _radius;
    }

    float SphereCollider::GetRadius() const {
        return radius;
    }
} // DivineBrush