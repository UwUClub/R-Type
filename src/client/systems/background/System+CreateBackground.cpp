#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/World.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createBackground()
    {
        auto &world = ECS::Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (auto &gameEvent : events) {
            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SPAWN) {
                continue;
            }
            bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

            if (isLocalPlayer) {
                display.freeRects(0);
                world.killEntity(0);
                AddEntity::addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                  Component::TypeEntity {false, false, false, false, false, false, true},
                                  Component::LoadedSprite {BACKGROUND_ASSET, nullptr,
                                                           new sf::IntRect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT},
                                                           new sf::IntRect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                  Component::HitBox {}, Component::IsAlive {false, 0});
                AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                  Component::TypeEntity {false, false, false, false, false, false, true},
                                  Component::LoadedSprite {BACKGROUND_ASSET, nullptr,
                                                           new sf::IntRect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT},
                                                           new sf::IntRect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                  Component::HitBox {}, Component::IsAlive {false, 0});
            }
        }
    }
} // namespace ECS
