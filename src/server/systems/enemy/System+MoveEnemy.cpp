#include "EwECS/World.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::moveEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                           Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        const auto size = aPos.size();

        for (size_t idx = 0; idx < size; idx++) {
            if (!aPos[idx].has_value() || !aSpeed[idx].has_value() || !aType[idx].has_value()) {
                continue;
            }

            auto &pos = aPos[idx].value();
            auto &speed = aSpeed[idx].value();
            auto &type = aType[idx].value();

            if (type.isEnemy) {
                pos.x -= speed.speed * world.getDeltaTime();
                if (pos.x < -ENEMY_TEX_WIDTH) {
                    world.killEntity(idx);
                }
            }
        }
    }
} // namespace ECS
