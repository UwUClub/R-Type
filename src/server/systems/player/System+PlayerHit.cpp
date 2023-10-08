#include "SparseArray.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    void System::playerHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();

        for (size_t playerId = 0; playerId < aType.size(); playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer) {
                continue;
            }
            for (size_t missileId = 0; missileId < aPos.size(); missileId++) {
                if (!aType[missileId].has_value() || !aType[missileId].value().isBullet) {
                    continue;
                }
                if ((aPos[playerId].value().x > aPos[missileId].value().x
                     && aPos[playerId].value().x < aPos[missileId].value().x + aHitBox[missileId].value().width
                     && aPos[playerId].value().y > aPos[missileId].value().y
                     && aPos[playerId].value().y < aPos[missileId].value().y + aHitBox[missileId].value().height)
                    || (aPos[playerId].value().x + aHitBox[playerId].value().width > aPos[missileId].value().x
                        && aPos[playerId].value().x + aHitBox[playerId].value().width
                               < aPos[missileId].value().x + aHitBox[missileId].value().width
                        && aPos[playerId].value().y > aPos[missileId].value().y
                        && aPos[playerId].value().y < aPos[missileId].value().y + aHitBox[missileId].value().height)) {
                    aIsAlive[playerId].value().isAlive = false;
                    // display.freeRects(missileId);
                    // world.killEntity(missileId);
                }
            }
        }
    }
} // namespace ECS
