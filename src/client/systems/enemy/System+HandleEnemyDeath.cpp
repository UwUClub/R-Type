#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::handleEnemyDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                  Core::SparseArray<Component::IsAlive> &aIsAlive,
                                  Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t enemy = 0; enemy < aType.size(); enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie < 0) {
                // display.freeRects(enemy);
                // world.killEntity(enemy);
            } else if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie == 0) {
                aSprites[enemy].value().path = EXPLOSION_ASSET;
                aSprites[enemy].value().texture = nullptr;
                aSprites[enemy].value().rect->h = EXPLOSION_TEX_HEIGHT;
                aSprites[enemy].value().rect->w = EXPLOSION_TEX_WIDTH;
                aSprites[enemy].value().rect->x = 146;
                aSprites[enemy].value().rect->y = 46;
                aIsAlive[enemy].value().timeToDie = 1;
            } else if (!aIsAlive[enemy].value().isAlive) {
                aIsAlive[enemy].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
