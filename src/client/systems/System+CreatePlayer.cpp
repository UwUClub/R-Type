#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createPlayer()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        int eventIndex = 0;
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_CONNECTION) {
                std::size_t onlineEntityId = static_cast<int>(gameEvent.getPayload()[0]);
                bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

                Component::TypeEntity entityType {false, true, false, false, false, false, false, onlineEntityId};
                if (isLocalPlayer) {
                    entityType = {true, false, false, false, false, false, false, onlineEntityId};
                }

                int color = static_cast<int>(gameEvent.getPayload()[2]);
                float posX = gameEvent.getPayload()[3];
                float posY = gameEvent.getPayload()[4];
                std::cout << "Player with color " << color << " joined" << std::endl;

                display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {PLAYER_SPEED}, entityType,
                                  Component::LoadedSprite {PLAYER_ASSET, nullptr,
                                                           new SDL_Rect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                                           new SDL_Rect {300, 15, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}},
                                  Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                  Component::IsAlive {true, 0});

                eventManager->removeEvent(eventIndex);
                eventIndex--;
            }
            eventIndex++;
        }
    }

} // namespace ECS