#pragma once
#include "GLTexture.h"

#include <string>

namespace Bengine {

    //Loads images into GLTextures
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(const std::string& filePath);
    };

}