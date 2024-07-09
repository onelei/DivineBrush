//
// Created by onelei on 2024/3/18.
//

#ifndef ENGINE_SAMPLE_SCENE_H
#define ENGINE_SAMPLE_SCENE_H

#include "../../Runtime/Component/scene.h"
#include "../../Runtime/Component/transform.h"
#include "../../Runtime/Render/Camera.h"
#include "../../Runtime/Render/Camera.h"
#include "../../Runtime/Component/GameObject.h"
#include "../../Runtime/Vector/Vector2.h"

namespace DivineBrush {

    class SampleScene : public Scene {
    public:
        SampleScene();

        void OnAwake() override;

        void OnUpdate() override;

        void OnDestroy() override;

        void CreateFont();

        void CreateUI();

        void TestAudio();

        void TestExportMesh();

    private:
        Camera *uiCamera;
        Camera *sceneCamera;
        Vector2 mousePosition;
        Transform *transform;
        Transform *uiCameraTransform;
        Transform *sceneCameraTransform;
    };

} // DivineBrush

#endif //ENGINE_SAMPLE_SCENE_H
