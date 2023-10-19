#include <cstddef>
#include <vector>
#include "Components.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveSpeedUp(Core::SparseArray<Component::Speed> &aSpeed,
                             Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::BONUS) {
                continue;
            }

            auto playerId = static_cast<size_t>(gameEvent.getEntityId());
            float const bonusType = gameEvent.getPayload()[0];

            if (bonusType == 1) {
                std::vector<float> payload = {static_cast<float>(playerId), 1};

                aSpeed[playerId].value().speed += 10;
                network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_BONUS), payload, aConnection);
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
