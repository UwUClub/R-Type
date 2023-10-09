#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::handleEnemyDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                  Core::SparseArray<Component::IsAlive> &aIsAlive,
                                  Core::SparseArray<Component::LoadedSprite> &aSprites,
                                  Core::SparseArray<Utils::Vector2f> &aPos)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t enemy = 0; enemy < aType.size(); enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie < 0) {
                display.freeRects(enemy);
                world.killEntity(enemy);
            } else if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie == 0) {
                aSprites[enemy].value().path = EXPLOSION_ASSET;
                aSprites[enemy].value().texture = nullptr;
                aSprites[enemy].value().rect->h = EXPLOSION_TEX_HEIGHT;
                aSprites[enemy].value().rect->w = EXPLOSION_TEX_WIDTH;
                aSprites[enemy].value().rect->x = 146;
                aSprites[enemy].value().rect->y = 46;
                aIsAlive[enemy].value().timeToDie = 1;
                if ((rand() % 3) != 0) {
                    display.addEntity(ECS::Utils::Vector2f {aPos[enemy].value().x, aPos[enemy].value().y},
                                      Component::Speed {BONUS_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, true, false},
                                      Component::LoadedSprite {BONUS_ASSET, nullptr,
                                                               new SDL_Rect {0, 0, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                                               new SDL_Rect {0, 0, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}},
                                      Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                      Component::IsAlive {true, 0});
                }
            } else if (!aIsAlive[enemy].value().isAlive) {
                aIsAlive[enemy].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
