#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::triggerEnemyShoot()
    {
        auto &display = SFMLDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (unsigned short i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::ENEMY_SHOOT) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::EnemyShotPayload>();

            display.addEntity(
                ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {MISSILES_SPEED},
                Component::TypeEntity {false, false, false, true, false, false, false, payload.bulletId},
                Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                         new sf::IntRect {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                         new sf::IntRect {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
                Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
