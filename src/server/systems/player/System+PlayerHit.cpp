#include "EwECS/SparseArray.hpp"
#include "EwECS/Utils.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    bool checkHitBox(Utils::Vector2f &aPosPlayer, Component::HitBox &aHitBoxPlayer, Utils::Vector2f &aPosObstacle,
                     Component::HitBox &aHitBoxObstacle)
    {
        if (aPosPlayer.x > aPosObstacle.x && aPosPlayer.x < aPosObstacle.x + aHitBoxObstacle.width
            && aPosPlayer.y > aPosObstacle.y && aPosPlayer.y < aPosObstacle.y + aHitBoxObstacle.height) {
            return (true);
        }
        if ((aPosPlayer.x + aHitBoxPlayer.width > aPosObstacle.x
             && aPosPlayer.x + aHitBoxPlayer.width < aPosObstacle.x + aHitBoxObstacle.width
             && aPosPlayer.y > aPosObstacle.y && aPosPlayer.y < aPosObstacle.y + aHitBoxObstacle.height)) {
            return (true);
        }
        if (aPosObstacle.x > aPosPlayer.x && aPosObstacle.x < aPosPlayer.x + aHitBoxPlayer.width
            && aPosObstacle.y > aPosPlayer.y && aPosObstacle.y < aPosPlayer.y + aHitBoxPlayer.height) {
            return (true);
        }
        return (false);
    }

    void System::playerHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        const auto size = aType.size();

        for (unsigned short playerId = 0; playerId < size; playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer) {
                continue;
            }

            const auto posSize = aPos.size();
            auto &posPlayer = aPos[playerId].value();
            auto &hitBoxPlayer = aHitBox[playerId].value();
            auto &isPlayerAlive = aIsAlive[playerId].value();

            for (unsigned short obstacleId = 0; obstacleId < posSize; obstacleId++) {
                if (!aType[obstacleId].has_value()
                    || (!aType[obstacleId].value().isBullet && !aType[obstacleId].value().isEnemy)) {
                    continue;
                }

                auto &posObstacle = aPos[obstacleId].value();
                auto &hitBoxObstacle = aHitBox[obstacleId].value();

                if (checkHitBox(posPlayer, hitBoxPlayer, posObstacle, hitBoxObstacle)) {
                    isPlayerAlive.isAlive = false;
                    world.killEntity(obstacleId);
                }
            }
        }
    }
} // namespace ECS
