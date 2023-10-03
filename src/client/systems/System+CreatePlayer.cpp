#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"

const constexpr float BACKGROUND_SPEED = 3;

namespace ECS {
    void System::createPlayer()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        int eventIndex = 0;

        for (auto &event : eventManager->getEventsByType(Event::EventType::GAME)) {
            auto &gameEvent = static_cast<RTypeProtocol::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RTypeProtocol::ClientEventType::PLAYER_CONNECTION) {
                std::size_t onlineEntityId = gameEvent.getOnlineEntityId();
                bool isLocalPlayer = gameEvent.getPayload()[0] == 1;

                Component::TypeEntity entityType {false, true, false, false, false, false, false, onlineEntityId};
                if (isLocalPlayer) {
                    entityType = {true, false, false, false, false, false, false, onlineEntityId};
                }

                int color = static_cast<int>(gameEvent.getPayload()[1]);
                float posX = gameEvent.getPayload()[2];
                float posY = gameEvent.getPayload()[3];
                std::cout << "Player with color " << color << " joined" << std::endl;

                display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {BACKGROUND_SPEED}, entityType,
                                  Component::LoadedSprite {PLAYER_ASSET, nullptr, new SDL_Rect {0, 0, 33, 17},
                                                           new SDL_Rect {300, 15, 33, 17}});

                eventManager->removeEvent(eventIndex);
                eventIndex--;
            }
            eventIndex++;
        }
    }

} // namespace ECS