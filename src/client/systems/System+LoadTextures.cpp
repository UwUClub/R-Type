#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        for (auto &aSprite : aSprites) {
            if (!aSprite.has_value() || aSprite.value().texture != nullptr) {
                continue;
            }
            aSprite.value().texture = display.getTexture(aSprite.value().path);
            if (aSprite.value().texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprite.value().path << std::endl;
            }
        }
    }
} // namespace ECS
