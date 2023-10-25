#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/World.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"

namespace ECS {
    void System::disconnectPlayer(Core::SparseArray<Component::Connection> &aConnection)
    {
        Core::World &world = Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (unsigned short i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::DISCONNECT) {
                continue;
            }

            unsigned short playerId = gameEvent.getEntityId();

            if (!aConnection[playerId].has_value()) {
                continue;
            }

            world.killEntity(playerId);
            server.removeClient(playerId);

            RType::Server::PlayerLeftPayload payload(playerId);
            server.broadcast(RType::ClientEventType::PLAYER_DISCONNECTION, payload, aConnection);

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
