//
// Created by onelei on 2024/3/18.
//

#ifndef ENGINE_SAMPLE_SCENE_H
#define ENGINE_SAMPLE_SCENE_H

#include "../../runtime/object/scene.h"
#include "../../runtime/object/transform.h"
#include "../../runtime/render/camera.h"
#include "../../runtime/render/camera.h"
#include "../../runtime/object/game_object.h"
#include "../../depends/vector/vector2f.h"

namespace DivineBrush {

    class SampleScene : public Scene {
    public:
        SampleScene();

        void Awake() override;

        void Update() override;

        void Destroy() override;

        void CreateFont();

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