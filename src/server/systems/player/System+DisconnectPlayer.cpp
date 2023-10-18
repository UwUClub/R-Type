#include <iostream>
#include <vector>
#include "Components.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::disconnectPlayer(Core::SparseArray<Component::Connection> &aConnection)
    {
        Core::World &world = Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::DISCONNECT) {
                continue;
            }

            size_t playerId = gameEvent.getEntityId();
            std::vector<float> payload = {static_cast<float>(playerId)};

            world.killEntity(playerId);
            server.removeClient(playerId);
            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_DISCONNECTION), payload, aConnection);
            toRemove.push_back(i);
        }
        for (auto &idx : toRemove) {
            eventManager->removeEvent<RType::ServerGameEvent>(idx);
        }
    }
} // namespace ECS
