#include <iostream>
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/SparseArray.hpp"
#include "System.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    void System::botHit(Core::SparseArray<Component::TypeEntity> &aType, Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        const auto size = aHitBox.size();

        for (size_t player = 0; player < size; player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer || !aHitBox[player].has_value()) {
                continue;
            }

            auto &hitBoxPlayer = aHitBox[player].value();

            if (!hitBoxPlayer.isColliding) {
                continue;
            }

            auto &collider = hitBoxPlayer.collidingId;

            if (!aType[collider].has_value() || !aType[collider].value().isBullet) {
                continue;
            }

            world.killEntity(collider);
        }
    }
} // namespace ECS
