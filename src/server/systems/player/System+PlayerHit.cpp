#include "EwECS/SparseArray.hpp"
#include "EwECS/Utils.hpp"
#include "System.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    void System::playerHit(Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        const auto size = aType.size();

        for (size_t playerId = 0; playerId < size; playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer || !aHitBox[playerId].has_value()
                || !aIsAlive[playerId].has_value()) {
                continue;
            }

            auto &hitBoxPlayer = aHitBox[playerId].value();
            auto &isPlayerAlive = aIsAlive[playerId].value();

            if (!isPlayerAlive.isAlive) {
                continue;
            }

            if (!hitBoxPlayer.isColliding) {
                continue;
            }

            auto &collider = hitBoxPlayer.collidingId;

            if (!aType[collider].has_value()
                || (!aType[collider].value().isEnemy && !aType[collider].value().isEnemyMissile)) {
                continue;
            }

            isPlayerAlive.isAlive = false;
            world.killEntity(collider);
        }
    }
} // namespace ECS
