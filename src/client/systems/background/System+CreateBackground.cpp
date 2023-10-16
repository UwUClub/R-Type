#include <iostream>
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "RayDisplayClass.hpp"
#include "Raylib.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::createBackground()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        RayDisplayClass &display = RayDisplayClass::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (auto &gameEvent : events) {
            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SPAWN) {
                bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

                if (isLocalPlayer) {
                    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr,
                                                               Rectangle {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                                                               Rectangle {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                    display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET,
                                                               nullptr,
                                                               {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                                                               Rectangle {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                }
            }
        }
    }
} // namespace ECS
