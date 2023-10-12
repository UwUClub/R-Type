#include <iostream>
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::killEnemy(Core::SparseArray<Component::TypeEntity> &aType,
                           Core::SparseArray<Component::IsAlive> &aIsAlive,
                           Core::SparseArray<Component::Connection> &aConnection)
    {
        auto &world = Core::World::getInstance();
        auto &server = Network::ServerHandler::getInstance();
        const auto size = aType.size();

        for (size_t enemyId = 0; enemyId < size; enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy || !aIsAlive[enemyId].has_value()) {
                continue;
            }
            if (!aIsAlive[enemyId].value().isAlive) {
                world.killEntity(enemyId);
                server.broadcast(static_cast<int>(RType::ClientEventType::ENEMY_DEATH), {static_cast<float>(enemyId)},
                                 aConnection);
            }
        }
    }
} // namespace ECS
