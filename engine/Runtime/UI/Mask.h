//
// Created by onelei on 2024/3/22.
//

#ifndef ENGINE_MASK_H
#define ENGINE_MASK_H

#include <string>
#include "Texture2D.h"
#include "UIBehaviour.h"

namespace DivineBrush::UI {

    class Mask : public UIBehaviour {
    public:
        Mask();

        ~Mask();

        void Load(std::string filename);

        void OnUpdate() override;

        void OnPreprocessRender() override;

        void OnPostprocessRender() override;

        void OnEnable() override;

        void OnDisable() override;

    private:
        unsigned int width = 0;
        unsigned int height = 0;
        std::string file_name;
        Texture2D *texture2d;
    };

} // DivineBrush

#endif //ENGINE_MASK_H
