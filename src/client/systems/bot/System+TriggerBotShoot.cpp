#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "SFMLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerBotShoot()
    {
        auto &display = SFMLDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SHOOT) {
                continue;
            }

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 3) {
                toRemove.push_back(i);
                continue;
            }

            size_t onlineBulletId = static_cast<int>(payload[0]);
            float posX = payload[1];
            auto posY = payload[2];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {BULLET_SPEED},
                              Component::TypeEntity {false, false, false, true, false, false, false, onlineBulletId},
                              Component::LoadedSprite {BULLET_ASSET, nullptr,
                                                       new sf::IntRect {207, 10, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT},
                                                       new sf::IntRect {0, 0, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}},
                              Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});
            toRemove.push_back(i);
        }
        for (auto &idx : toRemove) {
            eventManager->removeEvent<RType::ClientGameEvent>(idx);
        }
    }
} // namespace ECS