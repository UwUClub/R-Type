#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "System.hpp"
#include "Values.hpp"

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

            AddEntity::addEntity(
                ECS::Utils::Vector2f {posX, posY}, Component::Speed {BULLET_SPEED},
                Component::TypeEntity {false, false, false, true, false, false, false, onlineBulletId},
                Component::LoadedSprite {"config/missiles.json"},
                Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS