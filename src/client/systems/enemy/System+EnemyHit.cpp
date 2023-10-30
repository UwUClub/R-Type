#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        const auto size = aHitBox.size();

        for (size_t enemy = 0; enemy < size; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy || !aHitBox[enemy].has_value()) {
                continue;
            }

            auto &hitBoxEnemy = aHitBox[enemy].value();

            if (!hitBoxEnemy.isColliding) {
                continue;
            }

            auto &colliders = hitBoxEnemy.collidingId;

            for (auto &collider : colliders) {
                if (!aType[collider].has_value() || !aType[collider].value().isBullet) {
                    continue;
                }
                world.killEntity(collider);
            }
        }
    }
} // namespace ECS
