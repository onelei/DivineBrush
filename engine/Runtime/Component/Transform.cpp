//
// Created by onelei on 2024/2/29.
//

#include "Transform.h"
#include "rttr/registration.h"

using namespace rttr;

namespace DivineBrush {
    RTTR_REGISTRATION//注册反射
    {
        registration::class_<Transform>("Transform")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr)
                .property("position", &Transform::GetPosition, &Transform::SetPosition)
                .property("rotation", &Transform::GetRotation, &Transform::SetRotation)
                .property("scale", &Transform::GetScale, &Transform::SetScale);
    }

    Transform::Transform() : position(0.f), rotation(0.f), scale(1.f) {

    }

    Transform::~Transform() = default;

} // DivineBrush