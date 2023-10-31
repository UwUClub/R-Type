#include <iostream>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "ServerPackets.hpp"
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
            const auto &payload = gameEvent.getPayload<RType::Server::PlayerJoinedPayload>();

            if (payload.isReceiver) {
                world.killEntity(0);
                try {
                    auto idx = AddEntity::addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                         Component::TypeEntity {false, false, false, false, false, false, true},
                                         Component::LoadedSprite {"config/background.json"}, Component::HitBox {},
                                         Component::IsAlive {false, 0});
                    AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                         Component::TypeEntity {false, false, false, false, false, false, true},
                                         Component::LoadedSprite {"config/background2.json"}, Component::HitBox {},
                                         Component::IsAlive {false, 0});
                    world.emplaceEntityComponent<Component::MusicComponent>(idx, "assets/sounds/rtype.mp3", 100, true);
                } catch (const std::exception &e) {
                    ECS::Logger::error("[RType client exception] " + std::string(e.what()));
                }
            }
        }
    }
} // namespace ECS
