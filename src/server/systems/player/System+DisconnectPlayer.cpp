#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RType::ServerEventType::DISCONNECT) {
                size_t playerId = gameEvent.getEntityId();

                world.killEntity(playerId);
                server.removeClient(playerId);

                std::vector<float> payload = {static_cast<float>(playerId)};
                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_DISCONNECTION), payload, aConnection);

                eventManager->removeEvent(event);

                std::cout << "Player " << playerId << " left" << std::endl;
            }
        }
    }
} // namespace ECS
