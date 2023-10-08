#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"

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
                std::size_t onlineEntityId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                float posY = gameEvent.getPayload()[2];

                for (size_t i = 0; i < aType.size(); i++) {
                    if (!aType[i].has_value()) {
                        continue;
                    }
                    if (aType[i].value().onlineId == onlineEntityId) {
                        aPos[i].value().x = posX;
                        aPos[i].value().y = posY;
                        break;
                    }
                }

                eventManager->removeEvent(event);
            }
        }
    }

} // namespace ECS