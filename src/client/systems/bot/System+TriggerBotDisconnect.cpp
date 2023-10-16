#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotDisconnect(Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_DISCONNECTION) {
                if (gameEvent.getPayload().size() != 1) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                size_t onlineBotId = static_cast<size_t>(gameEvent.getPayload()[0]);
                size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);
                if (!aType[localBotId].has_value()) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                world.killEntity(localBotId);

                eventManager->removeEvent<RType::ClientGameEvent>(i);
                std::cout << "Player " << onlineBotId << " disconnected" << std::endl;
            }
        }
    }
} // namespace ECS
