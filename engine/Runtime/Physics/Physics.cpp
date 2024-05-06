//
// Created by onelei on 2024/4/26.
//

#include "Physics.h"

namespace DivineBrush {
    physx::PxDefaultAllocator Physics::pxDefaultAllocator;
    physx::PxDefaultErrorCallback Physics::pxDefaultErrorCallback;
    SimulationEventCallback Physics::simulationEventCallback;
    physx::PxFoundation *Physics::pxFoundation;
    physx::PxPhysics *Physics::pxPhysics;
    physx::PxDefaultCpuDispatcher *Physics::pxDefaultCpuDispatcher;
    physx::PxScene *Physics::pxScene;
    physx::PxPvd *Physics::pxPvd;
    bool Physics::enableCCD = true;

    void Physics::Init() {
        pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxDefaultAllocator, pxDefaultErrorCallback);
        pxPvd = PxCreatePvd(*pxFoundation);
        auto transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        pxPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
        pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, pxPvd);
        pxScene = CreatPxScene();
    }

    void Physics::FixUpdate() {
        pxScene->simulate(1.0f / 60.0f);
        pxScene->fetchResults(true);
    }

    physx::PxScene *Physics::CreatPxScene() {
        auto pxSceneDesc = physx::PxSceneDesc(pxPhysics->getTolerancesScale());
        pxSceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
        pxDefaultCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
        pxSceneDesc.cpuDispatcher = pxDefaultCpuDispatcher;
        pxSceneDesc.filterShader = SimulationFilterShader;
        pxSceneDesc.simulationEventCallback = &simulationEventCallback;
        if (enableCCD) {
            pxSceneDesc.flags |= physx::PxSceneFlag::eENABLE_CCD;
        }

        auto _pxScene = pxPhysics->createScene(pxSceneDesc);
        auto pxPvdSceneClient = _pxScene->getScenePvdClient();
        if (pxPvdSceneClient) {
            pxPvdSceneClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
            pxPvdSceneClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
            pxPvdSceneClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
        }
        return _pxScene;
    }

    physx::PxRigidDynamic *Physics::CreatePxRigidDynamic(glm::vec3 position, const char *name) {
        auto pxRigidDynamic = pxPhysics->createRigidDynamic(
                physx::PxTransform(physx::PxVec3(position.x, position.y, position.z)));
        pxRigidDynamic->setName(name);
        pxScene->addActor(*pxRigidDynamic);
        return pxRigidDynamic;
    }

    physx::PxRigidStatic *Physics::CreatePxRigidStatic(glm::vec3 position, const char *name) {
        auto pxRigidStatic = pxPhysics->createRigidStatic(
                physx::PxTransform(physx::PxVec3(position.x, position.y, position.z)));
        pxRigidStatic->setName(name);
        pxScene->addActor(*pxRigidStatic);
        return pxRigidStatic;
    }

    physx::PxMaterial *Physics::CreatePxMaterial(float staticFriction, float dynamicFriction, float restitution) {
        auto pxMaterial = pxPhysics->createMaterial(staticFriction, dynamicFriction, restitution);
        return pxMaterial;
    }

    physx::PxShape *Physics::CreateSphereShape(float radius, physx::PxMaterial *pxMaterial) {
        auto pxShape = pxPhysics->createShape(physx::PxSphereGeometry(radius), *pxMaterial);
        return pxShape;
    }

    physx::PxShape *Physics::CreateBoxShape(glm::vec3 size, physx::PxMaterial *pxMaterial) {
        auto pxShape = pxPhysics->createShape(physx::PxBoxGeometry(physx::PxVec3(size.x / 2, size.y / 2, size.z / 2)),
                                              *pxMaterial);
        return pxShape;
    }

    physx::PxFilterFlags
    Physics::SimulationFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
                                    physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
                                    physx::PxPairFlags &pairFlags, const void *constantBlock,
                                    physx::PxU32 constantBlockSize) {
        pairFlags = physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT |
                    physx::PxPairFlag::eNOTIFY_TOUCH_FOUND | physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
        auto isTrigger = filterData0.word0 == 1 || filterData1.word0 == 1;
        if (isTrigger) {
            pairFlags ^= physx::PxPairFlag::eSOLVE_CONTACT;
        }

        if (enableCCD) {
            pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_CCD | physx::PxPairFlag::eDETECT_CCD_CONTACT;
        }

        return physx::PxFilterFlags();
    }

    bool Physics::RaycastSingle(glm::vec3 &origin, glm::vec3 &direction, float distance, RaycastHit *raycastHit) {
        auto hitFlag = physx::PxHitFlag::ePOSITION | physx::PxHitFlag::eNORMAL | physx::PxHitFlag::eUV;
        physx::PxRaycastHit pxRaycastHit;
        if (physx::PxSceneQueryExt::raycastSingle(*pxScene, physx::PxVec3(origin.x, origin.y, origin.z),
                                                  physx::PxVec3(direction.x, direction.y, direction.z), distance,
                                                  hitFlag,
                                                  pxRaycastHit)) {
            raycastHit->SetPosition(glm::vec3(pxRaycastHit.position.x, pxRaycastHit.position.y,
                                              pxRaycastHit.position.z));
            auto gameObject = static_cast<GameObject *>(pxRaycastHit.shape->userData);
            raycastHit->SetGameObject(gameObject);
            return true;
        }
        return false;
    }

} // DivineBrush