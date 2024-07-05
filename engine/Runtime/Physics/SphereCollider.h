//
// Created by onelei on 2024/5/6.
//

#ifndef ENGINE_SPHERECOLLIDER_H
#define ENGINE_SPHERECOLLIDER_H

#include "Collider.h"

namespace DivineBrush {

    class SphereCollider : public Collider {
    public:
        SphereCollider();

        ~SphereCollider();

        void CreatePxShape() override;

        void SetRadius(float radius);

        float GetRadius() const;

    private:
        float radius = 1.0f;
    RTTR_ENABLE(Collider);
    };

} // DivineBrush

#endif //ENGINE_SPHERECOLLIDER_H
