#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::updateBotPosition(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        ;
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_POSITION) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent(event);
                    continue;
                }
                std::size_t onlineBotId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                float posY = gameEvent.getPayload()[2];

                size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);
                if (!aPos[localBotId].has_value()) {
                    eventManager->removeEvent(event);
                    continue;
                }
                aPos[localBotId].value().x = posX;
                aPos[localBotId].value().y = posY;

                eventManager->removeEvent(event);
            }
        }
    }

} // namespace ECS
