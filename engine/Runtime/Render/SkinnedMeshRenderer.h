//
// Created by onelei on 2024/5/23.
//

#ifndef ENGINE_SKINNEDMESHRENDERER_H
#define ENGINE_SKINNEDMESHRENDERER_H

#include "MeshRenderer.h"

namespace DivineBrush {

    class SkinnedMeshRenderer : public MeshRenderer {
    public:
        SkinnedMeshRenderer();

        ~SkinnedMeshRenderer();

        void OnUpdate() override;

        void Render() override;

    };

} // DivineBrush

#endif //ENGINE_SKINNEDMESHRENDERER_H
