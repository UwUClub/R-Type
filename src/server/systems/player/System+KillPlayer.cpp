#include <iostream>
#include "ClientGameEvent.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "IsAlive.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::killPlayer(Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::IsAlive> &aIsAlive,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        auto &world = Core::World::getInstance();
        auto &server = ECS::Network::ServerHandler::getInstance();
        const auto size = aType.size();

        for (size_t playerId = 0; playerId < size; playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer || !aIsAlive[playerId].has_value()) {
                continue;
            }
            if (!aIsAlive[playerId].value().isAlive) {
                RType::Server::PlayerDiedPayload payload(playerId);
                server.broadcast(RType::ClientEventType::PLAYER_DEATH, payload, aConnection);

                server.removeClient(playerId);
                world.killEntity(playerId);
            }
        }
    }
} // namespace ECS
