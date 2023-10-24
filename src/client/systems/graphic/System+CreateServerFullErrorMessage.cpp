#include <SFML/Graphics/Rect.hpp>
#include <iostream>
<<<<<<< HEAD
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> 0d29eee3be32994006876e9d9af91bad5767b555
#include "AddEntity.hpp"
=======
#include <vector>
>>>>>>> bf9ea2514a2d01e5c2b21eb96ab2e791b33bbd40
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/World.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "World.hpp"
>>>>>>> 0d29eee3be32994006876e9d9af91bad5767b555
=======
>>>>>>> bf9ea2514a2d01e5c2b21eb96ab2e791b33bbd40

namespace ECS {
    void System::createServerFullErrorMessage()
    {
        auto &world = ECS::Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

<<<<<<< HEAD
<<<<<<< HEAD
            if (gameEvent.getType() != RType::ClientEventType::SERVER_FULL) {
                continue;
=======
            if (gameEvent.getType() == RType::ClientEventType::SERVER_FULL) {
                display.freeRects(0);
                world.killEntity(0);
                std::cout << "Server is full" << std::endl;
                AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
                                                           SCREEN_HEIGHT / 2 - SERVER_FULL_MESSAGE_TEX_HEIGHT / 2},
                                     Component::Speed {0},
                                     Component::TypeEntity {false, false, false, false, false, false, true},
                                     Component::LoadedSprite {SERVER_FULL_MESSAGE, nullptr, nullptr,
                                                              new sf::IntRect {400, 15, SERVER_FULL_MESSAGE_TEX_WIDTH,
                                                                               SERVER_FULL_MESSAGE_TEX_HEIGHT}},
                                     Component::HitBox {}, Component::IsAlive {false, 0});

                eventManager->removeEvent(event);
>>>>>>> 0d29eee3be32994006876e9d9af91bad5767b555
            }
            display.freeRects(0);
            world.killEntity(0);
            AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
=======
            if (gameEvent.getType() != RType::ClientEventType::SERVER_FULL) {
                continue;
            }
            display.freeRects(0);
            world.killEntity(0);
            display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
>>>>>>> bf9ea2514a2d01e5c2b21eb96ab2e791b33bbd40
                                                    SCREEN_HEIGHT / 2 - SERVER_FULL_MESSAGE_TEX_HEIGHT / 2},
                              Component::Speed {0},
                              Component::TypeEntity {false, false, false, false, false, false, true},
                              Component::LoadedSprite {SERVER_FULL_MESSAGE, nullptr, nullptr,
                                                       new sf::IntRect {400, 15, SERVER_FULL_MESSAGE_TEX_WIDTH,
                                                                        SERVER_FULL_MESSAGE_TEX_HEIGHT}},
                              Component::HitBox {}, Component::IsAlive {false, 0});

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
