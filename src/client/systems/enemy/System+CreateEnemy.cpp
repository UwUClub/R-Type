#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"
namespace ECS {
    void System::createEnemy()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::ENEMY_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::EnemySpawnedPayload>();

            try {
                AddEntity::addEntity(
                    ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {ENEMY_SPEED},
                    Component::TypeEntity {false, false, true, false, false, false, false, payload.enemyId, false},
                    Component::LoadedSprite {"config/enemy.json"},
                    Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});
            } catch (const std::exception &e) {
                ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }

} // namespace ECS
