#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        SDL_SetRenderDrawColor(display._renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(display._renderer);
        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i]->texture == nullptr) {
                continue;
            }
            if (!aPos[i].has_value()) {
                continue;
            }
            aSprites[i]->srcRect.x = static_cast<int>(aPos[i].value().x);
            aSprites[i]->srcRect.y = static_cast<int>(aPos[i].value().y);
            SDL_RenderCopy(display._renderer, aSprites[i]->texture, &aSprites[i]->rect, &aSprites[i]->srcRect);
        }
    }
} // namespace ECS