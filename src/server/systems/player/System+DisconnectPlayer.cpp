#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "EwECS/World.hpp"
#include "ServerGameEvent.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"

namespace ECS {
    void System::disconnectPlayer(Core::SparseArray<Component::Connection> &aConnection)
    {
        Core::World &world = Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Network::ServerHandler &server = ECS::Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::DISCONNECT) {
                continue;
            }

            auto playerId = gameEvent.getEntityId();

            if (!aConnection[playerId].has_value()) {
                continue;
            }

            RType::Server::PlayerLeftPayload payload(playerId);
            server.broadcast(RType::ClientEventType::PLAYER_DISCONNECTION, payload, aConnection);
            world.killEntity(playerId);
            server.removeClient(playerId);
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
