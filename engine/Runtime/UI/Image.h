//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_IMAGE_H
#define ENGINE_IMAGE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "FreeImage.h"
#include "UIBehaviour.h"
#include "Texture2d.h"

namespace DivineBrush::UI {

    class Image : public UIBehaviour {
    public:
        Image();

        ~Image();

        void Load(std::string filename);

        void SetTexture2d(Texture2d *texture2d) {
            this->texture2d = texture2d;
        }

        Texture2d *GetTexture2d() {
            return texture2d;
        }

        void OnUpdate() override;

        void OnPreprocessRender() override;

        void OnPostprocessRender() override;

    private:
        std::string file_name;
        Texture2d *texture2d;
    };

} // DivineBrush

#endif //ENGINE_IMAGE_H
