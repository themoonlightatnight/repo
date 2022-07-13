#include "ResourceManager.h"

namespace Bengine {

    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(const std::string& texturePath) {
        return _textureCache.getTexture(texturePath);
    }

}