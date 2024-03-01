//
// Created by onelei on 2024/2/29.
//

#include "transform.h"
#include "rttr/registration.h"

using namespace rttr;

namespace DivineBrush {
    RTTR_REGISTRATION//注册反射
{
    registration::class_<Transform>("Transform")
    .

    constructor<>()(rttr::policy::ctor::as_raw_ptr)

    .property("position", &Transform::getPosition, &Transform::setPosition)
    .property("rotation", &Transform::getRotation, &Transform::setRotation)
    .property("scale", &Transform::getScale, &Transform::setScale);
}

} // DivineBrush