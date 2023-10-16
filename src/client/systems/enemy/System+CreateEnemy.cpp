#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createEnemy()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        RayDisplayClass &display = RayDisplayClass::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_SPAWN) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                std::size_t onlineEntityId = static_cast<std::size_t>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                float posY = gameEvent.getPayload()[2];

                display.addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {ENEMY_SPEED},
                    Component::TypeEntity {false, false, true, false, false, false, false, onlineEntityId},
                    Component::LoadedSprite {ENEMY_ASSET, nullptr, Rectangle {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                             Rectangle {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}},
                    Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});

                eventManager->removeEvent<RType::ClientGameEvent>(i);
            }
        }
    }

} // namespace ECS