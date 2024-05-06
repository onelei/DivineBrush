//
// Created by onelei on 2024/4/28.
//

#include "BoxCollider.h"
#include "rttr/registration.h"
#include "Physics.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<BoxCollider>("BoxCollider")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    BoxCollider::BoxCollider() {

    }

    BoxCollider::~BoxCollider() {

    }

    void BoxCollider::SetSize(glm::vec3 _size) {
        size = _size;
    }

    glm::vec3 BoxCollider::GetSize() {
        return size;
    }

    void BoxCollider::CreatePxShape() {
        Collider::CreatePxShape();
        if (pxShape == nullptr) {
            pxShape = Physics::CreateBoxShape(size, pxMaterial);
        }
    }
} // DivineBrush