#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "RayDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerEnemyShoot()
    {
        auto &display = RayDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_SHOOT) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                std::size_t onlineMissileId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                auto posY = gameEvent.getPayload()[2];

                display.addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {MISSILES_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false, onlineMissileId},
                    Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                             Rectangle {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                             Rectangle {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
                    Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});

                eventManager->removeEvent<RType::ClientGameEvent>(i);
            }
        }
    }
} // namespace ECS