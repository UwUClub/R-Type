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

namespace ECS {
    void System::triggerEnemyShoot()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];
            if (gameEvent.getType() != RType::ClientEventType::ENEMY_SHOOT) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::EnemyShotPayload>();

            try {
                AddEntity::addEntity(
                    ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {MISSILES_SPEED},
                    Component::TypeEntity {false, false, false, false, false, false, false, payload.bulletId, true},
                    Component::LoadedSprite {"config/bullet.json"},
                    Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});
            } catch (const std::exception &e) {
                ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
