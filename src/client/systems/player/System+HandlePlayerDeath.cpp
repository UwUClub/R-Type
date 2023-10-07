#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::handlePlayerDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t player = 0; player < aType.size(); player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer) {
                continue;
            }
            if (!aIsAlive[player].value().isAlive && aIsAlive[player].value().timeToDie < 0) {
                display.freeRects(player);
                world.killEntity(player);
            } else if (!aIsAlive[player].value().isAlive && aIsAlive[player].value().timeToDie == 0) {
                aSprites[player].value().path = EXPLOSION_ASSET;
                aSprites[player].value().texture = nullptr;
                aSprites[player].value().rect->h = EXPLOSION_TEX_HEIGHT;
                aSprites[player].value().rect->w = EXPLOSION_TEX_WIDTH;
                aSprites[player].value().rect->x = 146;
                aSprites[player].value().rect->y = 46;
                aIsAlive[player].value().timeToDie = 1;
            } else if (!aIsAlive[player].value().isAlive) {
                aIsAlive[player].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
