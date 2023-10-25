#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox,
                          Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();
        const auto size = aType.size();

        for (size_t enemyId = 0; enemyId < size; enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy || !aHitBox[enemyId].has_value()
                || !aIsAlive[enemyId].has_value()) {
                continue;
            }

            auto &hitBoxEnemy = aHitBox[enemyId].value();

            if (!hitBoxEnemy.isColliding) {
                continue;
            }

            auto &isAliveEnemy = aIsAlive[enemyId].value();

            if (!isAliveEnemy.isAlive) {
                continue;
            }

            auto &collider = hitBoxEnemy.collidingId;

            if (!aType[collider].has_value() || !aType[collider].value().isBullet) {
                continue;
            }

            isAliveEnemy.isAlive = false;
            std::cout << "enemy hit" << std::endl;
            world.killEntity(collider);
        }
    }
} // namespace ECS
