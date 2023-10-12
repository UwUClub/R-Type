#include <iostream>
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::killPlayer(Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::IsAlive> &aIsAlive,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        auto &world = Core::World::getInstance();
        auto &server = Network::ServerHandler::getInstance();
        const auto size = aType.size();

        for (size_t playerId = 0; playerId < size; playerId++) {
            if (!aType[playerId].has_value() || !aIsAlive[playerId].has_value() || !aType[playerId].value().isPlayer) {
                continue;
            }
            if (!aIsAlive[playerId].value().isAlive) {
                world.killEntity(playerId);
                server.removeClient(playerId);
                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_DEATH), {static_cast<float>(playerId)},
                                 aConnection);
            }
        }
    }
} // namespace ECS
