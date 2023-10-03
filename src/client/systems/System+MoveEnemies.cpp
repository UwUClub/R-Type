#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveEnemies(Core::SparseArray<Utils::Vector2f> &aPos, 
                        Core::SparseArray<Component::Speed> &aSpeed,
                        Core::SparseArray<Component::TypeEntity> &aType) 
    {
        auto &world = Core::World::getInstance();

        for (size_t idx = 0; idx < aPos.size(); idx++) {
            if (!aPos[idx].has_value()) {
                continue;
            }
            auto &pos = aPos[idx].value();
            auto &speed = aSpeed[idx].value();
            auto &type = aType[idx].value();
            if (type.isEnemy) {
                pos.x -= speed.speed * world.getDeltaTime();
                if (pos.x < -30) {
                    world.killEntity(idx);
                }
            }
        }

    } 

} // namespace ECS
