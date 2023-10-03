#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerNetworkHandler.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::welcomePlayers(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                Core::SparseArray<Component::TypeEntity> &aType)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();
        int eventIndex = 0;

        for (auto &event : eventManager->getEventsByType(Event::EventType::GAME)) {
            auto &gameEvent = static_cast<RTypeProtocol::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RTypeProtocol::ServerEventType::CONNECT) {
                size_t playerId = world.createEntity();
                float playerColor = static_cast<float>(network.getNumberClients());

                aPos.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
                aSpeed.insertAt(playerId, Component::Speed {10});
                aType.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false});

                network.broadcast(
                    {RTypeProtocol::ClientEventType::PLAYER_CONNECTION, playerId, {0, playerColor, 10, 10}});
                network.addClient(playerId, gameEvent.getClientEndpoint());
                network.send({RTypeProtocol::ClientEventType::PLAYER_CONNECTION, playerId, {1, playerColor, 10, 10}},
                             playerId);
                eventManager->removeEvent(eventIndex);
                eventIndex--;
            }
            eventIndex++;
        }
    }
} // namespace ECS