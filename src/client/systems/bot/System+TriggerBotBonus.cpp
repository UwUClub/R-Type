#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotBonus(Core::SparseArray<Component::Speed> &aSpeed,
                                 Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        auto &typeUtils = RType::TypeUtils::getInstance();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_BONUS) {
                continue;
            }

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 2) {
                toRemove.push_back(i);
                continue;
            }

            auto const onlineBotId = static_cast<const size_t>(payload[0]);
            std::size_t const localBotId = typeUtils.getEntityIdByOnlineId(aType, onlineBotId);
            float const type = payload[1];

            if (type == 1) {
                if (!aSpeed[localBotId].has_value()) {
                    toRemove.push_back(i);
                    continue;
                }
                aSpeed[localBotId].value().speed += (10.F);
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
