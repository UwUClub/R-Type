#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotBonus(Core::SparseArray<Component::Speed> &aSpeed,
                                 Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);
        auto &typeUtils = RType::TypeUtils::getInstance();

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_BONUS) {
                if (gameEvent.getPayload().size() != 2) {
                    eventManager->removeEvent(event);
                    continue;
                }

                std::size_t const onlineBotId = static_cast<const size_t>(gameEvent.getPayload()[0]);
                std::size_t const localBotId = typeUtils.getEntityIdByOnlineId(aType, onlineBotId);
                float const type = gameEvent.getPayload()[1];

                if (type == 1) {
                    if (!aSpeed[localBotId].has_value()) {
                        eventManager->removeEvent(event);
                        continue;
                    }
                    aSpeed[localBotId].value().speed += static_cast<float>(10);
                }
                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS