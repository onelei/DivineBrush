//
// Created by onelei on 2024/4/26.
//

#ifndef ENGINE_SIMULATIONEVENTCALLBACK_H
#define ENGINE_SIMULATIONEVENTCALLBACK_H

#include "PxPhysicsAPI.h"


namespace DivineBrush {

    class SimulationEventCallback : public physx::PxSimulationEventCallback {
    public:
        void onConstraintBreak(physx::PxConstraintInfo *constraints, physx::PxU32 count) override;

        void onWake(physx::PxActor **actors, physx::PxU32 count) override;

        void onSleep(physx::PxActor **actors, physx::PxU32 count) override;

        void onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs,
                       physx::PxU32 count) override;

        void onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count) override;

        void onAdvance(const physx::PxRigidBody *const *bodyBuffer, const physx::PxTransform *poseBuffer,
                       physx::PxU32 count) override;
    };

} // DivineBrush

#endif //ENGINE_SIMULATIONEVENTCALLBACK_H
