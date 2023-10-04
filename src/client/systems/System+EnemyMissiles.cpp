#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::enemyMissiles(Core::SparseArray<Utils::Vector2f> &aPos,
                               Core::SparseArray<Component::TypeEntity> &aType,
                               Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t idx = 0; idx < aPos.size(); idx++) {
            if (!aPos[idx].has_value()) {
                continue;
            }
            auto &pos = aPos[idx].value();
            auto &type = aType[idx].value();
            auto &isAlive = aIsAlive[idx].value();
            if (type.isEnemy && rand() % PROBABILTY_SHOOT_ENEMY == 0 && isAlive.isAlive) {
                display.addEntity(
                    ECS::Utils::Vector2f {static_cast<float>(pos.x - MISSILES_TEX_WIDTH),
                                          static_cast<float>(pos.y + ENEMY_TEX_HEIGHT / 2 - MISSILES_TEX_HEIGHT / 2)},
                    Component::Speed {MISSILES_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false},
                    Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                             new SDL_Rect {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                             new SDL_Rect {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
                    Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});
            }
        }
    }
} // namespace ECS