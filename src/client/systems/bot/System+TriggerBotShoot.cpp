#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "EwECS/Sound/SoundComponent.hpp"

namespace ECS {
    void System::triggerBotShoot()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();
        auto &world = Core::World::getInstance();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SHOOT) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerShotPayload>();

            try {
                auto entity_id = AddEntity::addEntity(
                    ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {BULLET_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false, payload.bulletId, false},
                    Component::LoadedSprite {"config/missiles.json"},
                    Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});
                world.emplaceEntityComponent<Component::SoundComponent>(entity_id, "assets/sounds/pew.mp3", 40, false);
            } catch (const std::exception &e) {
                ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS