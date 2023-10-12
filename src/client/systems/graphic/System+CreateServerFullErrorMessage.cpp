#include <iostream>
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::createServerFullErrorMessage()
    {
        auto &world = ECS::Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        RayDisplayClass &display = RayDisplayClass::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::SERVER_FULL) {
                world.killEntity(0);
                std::cout << "Server is full" << std::endl;
                display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
                                                        SCREEN_HEIGHT / 2 - SERVER_FULL_MESSAGE_TEX_HEIGHT / 2},
                                  Component::Speed {0},
                                  Component::TypeEntity {false, false, false, false, false, false, true},
                                  Component::LoadedSprite {SERVER_FULL_MESSAGE,
                                                           nullptr,
                                                           {},
                                                           Rectangle {400, 15, SERVER_FULL_MESSAGE_TEX_WIDTH,
                                                                      SERVER_FULL_MESSAGE_TEX_HEIGHT}},
                                  Component::HitBox {}, Component::IsAlive {false, 0});

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
