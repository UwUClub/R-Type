#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotDisconnect(Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_DISCONNECTION) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerLeftPayload>();

            unsigned short localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, payload.playerId);

            if (!aType[localBotId].has_value()) {
                toRemove.push_back(i);
                continue;
            }
            world.killEntity(localBotId);
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
