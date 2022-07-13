#pragma once
#include "GLTexture.h"
#include <glm/glm.hpp>
#include <map>
namespace Bengine
{
    struct TileSheetXML
    {
        TileSheetXML()
        {
            texture.isFromSpriteSheet = true;
        }
        void init(const GLTexture& texture) 
        {
            this->texture = texture;
        }
        const glm::vec2 &getSpriteDimension  (const std::string& spriteSheetPath);
        const glm::vec4 &getPosDesXML  (const std::string& spriteSheetPath, const std::string& subName);
        GLTexture texture;
        glm::vec4 m_uv;
        glm::ivec2 dims;
        std::map<std::pair<std::string, std::string>, glm::vec4> map;
        std::map<std::string, glm::vec2> spriteDimsMap;
        glm::vec2 m_spriteDimension;
    };
}