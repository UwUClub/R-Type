#include <iostream>
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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SPAWN) {
                bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

                if (isLocalPlayer) {
                    // Setup background
                    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                               new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                    display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                               new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                }
            }
        }
    }
} // namespace ECS
