//
// Created by onelei on 2024/4/26.
//

#include "PhysicMaterial.h"

namespace DivineBrush {
    void PhysicMaterial::SetDynamicFriction(float _dynamicFriction) {
        dynamicFriction = _dynamicFriction;
    }

    void PhysicMaterial::SetStaticFriction(float _staticFriction) {
        staticFriction = _staticFriction;
    }

    void PhysicMaterial::SetRestitution(float _restitution) {
        restitution = _restitution;
    }

    float PhysicMaterial::GetDynamicFriction() const {
        return dynamicFriction;
    }

    float PhysicMaterial::GetStaticFriction() const {
        return staticFriction;
    }

    float PhysicMaterial::GetRestitution() const {
        return restitution;
    }
} // DivineBrush