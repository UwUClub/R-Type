#include <cstddef>
#include <iostream>
#include <vector>
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"

namespace ECS {
    void System::receiveAknowledgment(Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ServerEventType::AKNOWLEDGMENT) {
                size_t playerId = gameEvent.getEntityId();

                if (aConnection[playerId].has_value()) {
                    auto &connection = aConnection[playerId].value();

                    connection.status = Network::ConnectionStatus::CONNECTED;
                    connection.age = 0;
                }
                toRemove.push_back(i);
            }
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
