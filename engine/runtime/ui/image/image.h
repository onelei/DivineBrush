//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_IMAGE_H
#define ENGINE_IMAGE_H

#include <GL/glew.h>
#include "FreeImage.h"
#include "../behavior/ui_behaviour.h"

namespace DivineBrush::UI {

    class Image : public UIBehaviour {
    public:
        Image();

        ~Image();

        static Image *LoadImage(char *filename);
        static GLuint LoadImageToTextureID(char* filename);

    public:
        unsigned int width = 0;
        unsigned int height = 0;
        BYTE *pixels = nullptr;

    private:
        static void FlipImageVertically(Image *image);

        static void FlipImageVertically(unsigned int width, unsigned int height, unsigned int size, BYTE *pixels,BYTE *flippedPixels);
    };

} // DivineBrush

#endif //ENGINE_IMAGE_H
