#include <iostream>
#include "ClientGameEvent.hpp"
#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::killEnemy(Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::Connection> &aConnection,
                           Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::HitBox> &aHitBox,
                           Core::SparseArray<Component::Speed> &aSpeed)
    {
        auto &world = Core::World::getInstance();
        auto &server = Network::ServerHandler::getInstance();
        const auto size = aType.size();

        for (size_t enemyId = 0; enemyId < size; enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy || !aIsAlive[enemyId].has_value()) {
                continue;
            }
            if (!aIsAlive[enemyId].value().isAlive) {
                auto bonusId = world.createEntity();
                aPos.insertAt(bonusId, ECS::Utils::Vector2f {aPos[enemyId].value().x, aPos[enemyId].value().y});
                aSpeed.insertAt(bonusId, Component::Speed {BONUS_SPEED});
                aType.insertAt(bonusId, Component::TypeEntity {false, false, false, false, false, true, false});
                aHitBox.insertAt(bonusId, Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT});

                RType::Server::EnemyDiedPayload payload(enemyId, bonusId);
                server.broadcast(RType::ClientEventType::ENEMY_DEATH, payload, aConnection);

                world.killEntity(enemyId);
            }
        }
    }
} // namespace ECS
