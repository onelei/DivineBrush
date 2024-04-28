//
// Created by onelei on 2024/4/26.
//

#ifndef ENGINE_PHYSICS_H
#define ENGINE_PHYSICS_H

#include <PxPhysicsAPI.h>
#include <glm/vec3.hpp>
#include "SimulationEventCallback.h"
#include "RaycastHit.h"

namespace DivineBrush {

    class Physics {
    public:
        static void Init();

        static void FixUpdate();

        static physx::PxScene *CreatPxScene();

        static physx::PxRigidDynamic *CreatePxRigidDynamic(glm::vec3 position, char *name);

        static physx::PxRigidStatic *CreatePxRigidStatic(glm::vec3 position, char *name);

        static physx::PxMaterial *CreatePxMaterial(float staticFriction, float dynamicFriction, float restitution);

        static physx::PxShape *CreateSphereShape(float radius, physx::PxMaterial *pxMaterial);

        static physx::PxShape *CreateBoxShape(glm::vec3 size, physx::PxMaterial *pxMaterial);

        static physx::PxFilterFlags
        SimulationFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
                               physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
                               physx::PxPairFlags &pairFlags, const void *constantBlock,
                               physx::PxU32 constantBlockSize);

        static bool RaycastSingle(glm::vec3 &origin, glm::vec3 &direction, float distance, RaycastHit *raycastHit);

        static bool GetEnableCCD() { return enableCCD; }

        static void SetEnableCCD(bool enable) {
            enableCCD = enable;
        }

    private:
        static physx::PxDefaultAllocator pxDefaultAllocator;
        static physx::PxDefaultErrorCallback pxDefaultErrorCallback;
        static SimulationEventCallback simulationEventCallback;
        static physx::PxFoundation *pxFoundation;
        static physx::PxPhysics *pxPhysics;
        static physx::PxDefaultCpuDispatcher *pxDefaultCpuDispatcher;
        static physx::PxScene *pxScene;
        static physx::PxPvd *pxPvd;
        static bool enableCCD;
    };

} // DivineBrush

#endif //ENGINE_PHYSICS_H
