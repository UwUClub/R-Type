#include <iostream>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createBackground()
    {
        auto &world = ECS::Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (auto &gameEvent : events) {
            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SPAWN) {
                continue;
            }
            bool isLocalPlayer = gameEvent.getPayload()[1] == 1;

            if (isLocalPlayer) {
                world.killEntity(0);
                AddEntity::addEntity(
                    ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                    Component::TypeEntity {false, false, false, false, false, false, true},
                    Component::LoadedSprite {BACKGROUND_ASSET, nullptr, 400, 15, SCREEN_WIDTH, SCREEN_HEIGHT},
                    Component::HitBox {}, Component::IsAlive {false, 0});
                AddEntity::addEntity(
                    ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                    Component::TypeEntity {false, false, false, false, false, false, true},
                    Component::LoadedSprite {BACKGROUND_ASSET, nullptr, 400, 15, SCREEN_WIDTH, SCREEN_HEIGHT},
                    Component::HitBox {}, Component::IsAlive {false, 0});
            }
        }
    }
} // namespace ECS
