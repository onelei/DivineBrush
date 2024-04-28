//
// Created by onelei on 2024/4/26.
//

#include "SimulationEventCallback.h"
#include "../../depends/debug/Debug.h"
#include "../Component/GameObject.h"

namespace DivineBrush {
    void SimulationEventCallback::onConstraintBreak(physx::PxConstraintInfo *constraints, physx::PxU32 count) {

    }

    void SimulationEventCallback::onWake(physx::PxActor **actors, physx::PxU32 count) {

    }

    void SimulationEventCallback::onSleep(physx::PxActor **actors, physx::PxU32 count) {

    }

    void
    SimulationEventCallback::onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs,
                                       physx::PxU32 count) {
        while (count--) {
            const physx::PxContactPair &current = *pairs++;
            for (int i = 0; i < 2; ++i) {
                auto shape = current.shapes[i];
                auto isTrigger = shape->getSimulationFilterData().word0 & 0x1;
                if (!isTrigger) {
                    continue;
                }
                auto other = current.shapes[i ^ 1];
                auto otherGameObject = static_cast<GameObject *>(other->userData);
                if (!otherGameObject->IsActive())
                    continue;
                auto gameObject = static_cast<GameObject *>(shape->userData);
                if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND || physx::PxPairFlag::eNOTIFY_TOUCH_CCD) {
                    otherGameObject->ForeachComponent([&](Component *component) {
                        component->OnTriggerEnter(gameObject);
                    });
                }
                if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST) {
                    otherGameObject->ForeachComponent([&](Component *component) {
                        component->OnTriggerExit(gameObject);
                    });
                }
            }
        }
    }

    void SimulationEventCallback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count) {
        while (count--) {
            const physx::PxTriggerPair &current = *pairs++;
            if (current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
                Debug::Log("onEnterTrigger");
            }
            if (current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST) {
                Debug::Log("onExitTrigger");
            }
        }
    }

    void SimulationEventCallback::onAdvance(const physx::PxRigidBody *const *bodyBuffer,
                                            const physx::PxTransform *poseBuffer, physx::PxU32 count) {

    }
} // DivineBrush