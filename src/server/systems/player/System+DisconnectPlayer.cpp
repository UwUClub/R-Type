#include <iostream>
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

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];
            if (gameEvent.getType() == RType::ServerEventType::DISCONNECT) {
                size_t playerId = gameEvent.getEntityId();

                world.killEntity(playerId);
                server.removeClient(playerId);

                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_DISCONNECTION),
                                 {static_cast<float>(playerId)}, aConnection);

                eventManager->removeEvent<RType::ServerGameEvent>(i);

                std::cout << "Player " << playerId << " left" << std::endl;
            }
        }
    }
} // namespace ECS
