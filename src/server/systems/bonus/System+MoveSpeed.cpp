#include <cstddef>
#include <vector>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "EwECS/World.hpp"
#include "ServerGameEvent.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"
namespace ECS {
    void System::moveSpeedUp(Core::SparseArray<Component::Speed> &aSpeed,
                             Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Network::ServerHandler &server = ECS::Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::BONUS) {
                continue;
            }

            // auto playerId = gameEvent.getEntityId();
            // float const bonusType = gameEvent.getPayload()[0];

            // if (bonusType == 1) {
            //     aSpeed[playerId].value().speed += 10;
            //     server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_BONUS), payload, aConnection);
            // } else {
            //     network.send(ECS::Network::PacketHeader(ERROR_PACKET_TYPE), gameEvent.getClientEndpoint());
            // }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
