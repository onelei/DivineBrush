//
// Created by onelei on 2024/3/18.
//

#include <rttr/registration.h>
#include "Scene.h"

namespace DivineBrush {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Scene>("Scene")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Scene::Scene() {

    }

    Scene::~Scene() {

    }

} // DivineBrush