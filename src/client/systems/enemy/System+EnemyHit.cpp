#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        const auto size = aHitBox.size();

        for (size_t enemy = 0; enemy < size; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy || !aHitBox[enemy].has_value()) {
                continue;
            }

            auto &hitBoxEnemy = aHitBox[enemy].value();

            if (!hitBoxEnemy.isColliding) {
                continue;
            }

            auto &collider = hitBoxEnemy.collidingId;

            if (!aType[collider].has_value() || !aType[collider].value().isBullet) {
                continue;
            }

            display.freeRects(collider);
            world.killEntity(collider);
        }
    }
} // namespace ECS
