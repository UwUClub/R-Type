#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include <SDL2/SDL_image.h>

namespace ECS {
    void System::loadTextures(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i].value().texture != nullptr)
                continue;
            aSprites[i].value().texture = IMG_LoadTexture(display._renderer, aSprites[i].value().path.c_str());
            if (aSprites[i].value().texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprites[i].value().path << std::endl;
            }
        }
    }
} // namespace ECS