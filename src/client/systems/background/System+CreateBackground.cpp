#include <iostream>
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::createBackground()
    {
        auto &world = ECS::Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        RayDisplayClass &display = RayDisplayClass::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SPAWN) {
                bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

                if (isLocalPlayer) {
                    world.killEntity(0);
                    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET,
                                                               nullptr,
                                                               {},
                                                               Rectangle {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                    display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, false, true},
                                      Component::LoadedSprite {BACKGROUND_ASSET,
                                                               nullptr,
                                                               {},
                                                               Rectangle {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                      Component::HitBox {}, Component::IsAlive {false, 0});
                }
            }
        }
    }
} // namespace ECS
