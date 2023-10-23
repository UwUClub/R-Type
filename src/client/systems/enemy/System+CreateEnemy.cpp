#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "SFMLDisplayClass.hpp"
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

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::ENEMY_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 3) {
                toRemove.push_back(i);
                continue;
            }

            auto onlineEntityId = static_cast<std::size_t>(payload[0]);
            float posX = payload[1];
            float posY = payload[2];

            AddEntity::addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {ENEMY_SPEED},
                                 Component::TypeEntity {false, false, true, false, false, false, false, onlineEntityId},
                                 Component::LoadedSprite {ENEMY_ASSET, nullptr,
                                                          new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                                          new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}},
                                 Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }

} // namespace ECS
