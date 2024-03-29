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
#include "../../depends/vector/vector2f.h"

namespace DivineBrush {

    class SampleScene : public Scene {
    public:
        SampleScene();

        void OnAwake() override;

        void OnUpdate() override;

        void OnDestroy() override;

        void CreateFont();

        void CreateUI();

    private:
        Camera *camera;
        Camera *camera_2;
        Vector2f mousePosition;
        Transform *transform;
        Transform *camera_transform;
        Transform *transform_camera_2;
    };

} // DivineBrush

#endif //ENGINE_SAMPLE_SCENE_H
