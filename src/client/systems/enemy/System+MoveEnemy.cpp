#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                           Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();
        const auto size = aPos.size();

        for (std::size_t idx = 0; idx < size; idx++) {
            if (!aPos[idx].has_value() || !aSpeed[idx].has_value() || !aType[idx].has_value()) {
                continue;
            }
            auto &type = aType[idx].value();
            if (!type.isEnemy) {
                continue;
            }
            auto &pos = aPos[idx].value();
            auto &speed = aSpeed[idx].value();

            pos.x -= speed.speed * world.getDeltaTime();
            if (pos.x > -ENEMY_TEX_WIDTH) {
                continue;
            }
            display.freeRects(idx);
            world.killEntity(idx);
        }
    }
} // namespace ECS
