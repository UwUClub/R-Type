#include <cstddef>
#include <iostream>
#include "Components.hpp"
#include "EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"

namespace ECS {
    void System::receiveAknowledgment(Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ServerEventType::AKNOWLEDGMENT) {
                size_t playerId = gameEvent.getEntityId();

                if (aConnection[playerId].has_value()) {
                    std::cout << "Got aknowledgment from " << playerId << std::endl;
                    aConnection[playerId].value().status = Network::ConnectionStatus::CONNECTED;
                    aConnection[playerId].value().age = 0;
                }
                eventManager->removeEvent<RType::ServerGameEvent>(i);
            }
        }
    }
} // namespace ECS
