#include "SparseArray.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    bool checkHitBox(size_t playerId, size_t obstacleId, Core::SparseArray<Utils::Vector2f> &aPos,
                     Core::SparseArray<Component::HitBox> &aHitBox)
    {
        if (aPos[playerId].value().x > aPos[obstacleId].value().x
            && aPos[playerId].value().x < aPos[obstacleId].value().x + aHitBox[obstacleId].value().width
            && aPos[playerId].value().y > aPos[obstacleId].value().y
            && aPos[playerId].value().y < aPos[obstacleId].value().y + aHitBox[obstacleId].value().height) {
            return (true);
        } else if ((aPos[playerId].value().x + aHitBox[playerId].value().width > aPos[obstacleId].value().x
                    && aPos[playerId].value().x + aHitBox[playerId].value().width
                           < aPos[obstacleId].value().x + aHitBox[obstacleId].value().width
                    && aPos[playerId].value().y > aPos[obstacleId].value().y
                    && aPos[playerId].value().y < aPos[obstacleId].value().y + aHitBox[obstacleId].value().height)) {
            return (true);
        } else if (aPos[obstacleId].value().x > aPos[playerId].value().x
                   && aPos[obstacleId].value().x < aPos[playerId].value().x + aHitBox[playerId].value().width
                   && aPos[obstacleId].value().y > aPos[playerId].value().y
                   && aPos[obstacleId].value().y < aPos[playerId].value().y + aHitBox[playerId].value().height) {
            return (true);
        }
        return (false);
    }

    void System::playerHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();

        for (size_t playerId = 0; playerId < aType.size(); playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer) {
                continue;
            }
            for (size_t obstacleId = 0; obstacleId < aPos.size(); obstacleId++) {
                if (!aType[obstacleId].has_value()
                    || (!aType[obstacleId].value().isBullet && !aType[obstacleId].value().isEnemy)) {
                    continue;
                }
                if (checkHitBox(playerId, obstacleId, aPos, aHitBox)) {
                    aIsAlive[playerId].value().isAlive = false;
                    world.killEntity(obstacleId);
                }
            }
        }
    }
} // namespace ECS
