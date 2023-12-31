#include <iostream>
#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "System.hpp"
#include "Values.hpp"

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

            if (gameEvent.getType() != RType::ClientEventType::SERVER_FULL) {
                continue;
            }
            world.killEntity(0);
            try {
                AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
                                                           SCREEN_HEIGHT / 2 - SERVER_FULL_MESSAGE_TEX_HEIGHT / 2},
                                     Component::Speed {0},
                                     Component::TypeEntity {false, false, false, false, false, false, true},
                                     Component::LoadedSprite {"serverMessage.json"}, Component::HitBox {},
                                     Component::IsAlive {false, 0});
            } catch (const std::exception &e) {
                ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
