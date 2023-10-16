#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotBonus(Core::SparseArray<Component::Speed> &aSpeed,
                                 Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        auto &typeUtils = RType::TypeUtils::getInstance();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_BONUS) {
                if (gameEvent.getPayload().size() != 2) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }

                std::size_t const onlineBotId = static_cast<const size_t>(gameEvent.getPayload()[0]);
                std::size_t const localBotId = typeUtils.getEntityIdByOnlineId(aType, onlineBotId);
                float const type = gameEvent.getPayload()[1];

                if (type == 1) {
                    if (!aSpeed[localBotId].has_value()) {
                        eventManager->removeEvent<RType::ClientGameEvent>(i);
                        continue;
                    }
                    aSpeed[localBotId].value().speed += static_cast<float>(10);
                }
                eventManager->removeEvent<RType::ClientGameEvent>(i);
            }
        }
    }
} // namespace ECS