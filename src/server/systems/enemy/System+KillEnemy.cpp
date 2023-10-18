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

        for (size_t enemyId = 0; enemyId < aType.size(); enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy) {
                continue;
            }
            if (!aIsAlive[enemyId].value().isAlive) {
                world.killEntity(enemyId);
                std::cout << "Enemy " << enemyId << " killed" << std::endl;
                std::vector<float> payload = {static_cast<float>(enemyId)};
                server.broadcast(static_cast<int>(RType::ClientEventType::ENEMY_DEATH), payload, aConnection);
            }
        }
    }
} // namespace ECS
