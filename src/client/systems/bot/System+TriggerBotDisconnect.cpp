#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotDisconnect(Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_DISCONNECTION) {
                if (gameEvent.getPayload().size() != 1) {
                    eventManager->removeEvent(event);
                    continue;
                }
                size_t onlineBotId = static_cast<size_t>(gameEvent.getPayload()[0]);
                size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);
                if (!aType[localBotId].has_value()) {
                    eventManager->removeEvent(event);
                    continue;
                }
                world.killEntity(localBotId);

                eventManager->removeEvent(event);
                std::cout << "Player " << onlineBotId << " disconnected" << std::endl;
            }
        }
    }
} // namespace ECS
