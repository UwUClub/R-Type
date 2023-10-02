#include "System.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include <SDL2/SDL_image.h>


namespace ECS {
    void System::displayEntities(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        SDL_SetRenderDrawColor(display._renderer, 0, 0, 0, 255);
        SDL_RenderClear(display._renderer);
        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i].value().texture == nullptr)
                continue;
            aSprites[i].value().srcRect.x = aPos[i].value().x;
            aSprites[i].value().srcRect.y = aPos[i].value().y;
            SDL_RenderCopy(display._renderer, aSprites[i].value().texture, &aSprites[i].value().rect,
                           &aSprites[i].value().srcRect);
        }
    }
}