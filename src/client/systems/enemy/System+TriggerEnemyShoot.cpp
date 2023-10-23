#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
<<<<<<< HEAD
=======
#include "World.hpp"
{
    auto &display = SFMLDisplayClass::getInstance();
    Event::EventManager *eventManager = Event::EventManager::getInstance();
    auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
    const auto size = events.size();
    std::vector<size_t> toRemove;

    for (size_t i = 0; i < size; i++) {
        auto &gameEvent = events[i];

        if (gameEvent.getType() != RType::ClientEventType::ENEMY_SHOOT) {
            continue;
        }

        const auto &payload = gameEvent.getPayload();

        if (payload.size() != 3) {
            toRemove.push_back(i);
            continue;
        }

        std::size_t onlineMissileId = static_cast<int>(payload[0]);
        float posX = payload[1];
        auto posY = payload[2];

        AddEntity::addEntity(
            ECS::Utils::Vector2f {posX, posY}, Component::Speed {MISSILES_SPEED},
            Component::TypeEntity {false, false, false, true, false, false, false, onlineMissileId},
            Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                     new sf::IntRect {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                     new sf::IntRect {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
            Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});
        toRemove.push_back(i);
    }
    eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
}
} // namespace ECS
