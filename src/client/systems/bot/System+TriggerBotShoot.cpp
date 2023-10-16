#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "RayDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerBotShoot()
    {
        auto &display = RayDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SHOOT) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                size_t onlineBulletId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                auto posY = gameEvent.getPayload()[2];

                display.addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {BULLET_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false, onlineBulletId},
                    Component::LoadedSprite {BULLET_ASSET, nullptr,
                                             Rectangle {207, 10, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT},
                                             Rectangle {0, 0, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}},
                    Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});

                eventManager->removeEvent<RType::ClientGameEvent>(i);
            }
        }
    }
} // namespace ECS
