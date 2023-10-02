#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerNetworkHandler.hpp"
#include "System.hpp"

namespace ECS {
    void System::welcomePlayers(Core::World &world, Core::SparseArray<Utils::Vector2f> &aPos,
                                Core::SparseArray<Utils::Speed> &aSpeed, Core::SparseArray<Utils::TypeEntity> &aType)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();

        for (auto &event : eventManager->getEvents()) {
            if (event->getType() == ECS::Event::EventType::GAME) {
                auto &gameEvent = static_cast<RTypeProtocol::ServerGameEvent &>(*event);

                if (gameEvent.getType() == RTypeProtocol::ServerEventType::CONNECT) {
                    size_t idPlayer = world.createEntity();

                    aPos.insertAt(idPlayer, ECS::Utils::Vector2f {10, 10});
                    aSpeed.insertAt(idPlayer, ECS::Utils::Speed {10});
                    aType.insertAt(idPlayer, ECS::Utils::TypeEntity {true, false, false, false, false});

                    network.addClient(idPlayer, gameEvent.getClientEndpoint());

                    // TODO: send connect packet to every other clients
                }
            }
        }
    }
} // namespace ECS
