#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createEnemy()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (unsigned short i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::ENEMY_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::EnemySpawnedPayload>();

            display.addEntity(ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {ENEMY_SPEED},
                              Component::TypeEntity {false, false, true, false, false, false, false, payload.enemyId},
                              Component::LoadedSprite {ENEMY_ASSET, nullptr,
                                                       new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                                       new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}},
                              Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }

} // namespace ECS
