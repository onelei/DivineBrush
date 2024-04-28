//
// Created by onelei on 2024/4/26.
//

#ifndef ENGINE_PHYSICMATERIAL_H
#define ENGINE_PHYSICMATERIAL_H

namespace DivineBrush {

    class PhysicMaterial {
    public:
        PhysicMaterial() = default;

        ~PhysicMaterial() = default;

        void SetDynamicFriction(float _dynamicFriction);

        void SetStaticFriction(float _staticFriction);

        void SetRestitution(float _restitution);

        float GetDynamicFriction() const;

        float GetStaticFriction() const;

        float GetRestitution() const;

    private:
        float dynamicFriction = 0.5f;
        float staticFriction = 0.5f;
        float restitution = 0.5f;
    };

} // DivineBrush

#endif //ENGINE_PHYSICMATERIAL_H
