#pragma once
#include <GL/glew.h>
#include <string>
namespace Bengine 
{
    struct GLTexture 
    {
        std::string filePath = "";
        std::string name = "";
        GLuint id;
        int width;
        int height;
        bool isFromSpriteSheet = false;
    };
}