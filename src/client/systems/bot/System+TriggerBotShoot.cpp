#include <SFML/Graphics/Rect.hpp>
#include "AddEntity.hpp"
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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SHOOT) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent(event);
                    continue;
                }
                size_t onlineBulletId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                auto posY = gameEvent.getPayload()[2];

                AddEntity::addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {BULLET_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false, onlineBulletId},
                    Component::LoadedSprite {BULLET_ASSET, nullptr,
                                             new sf::IntRect {207, 10, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT},
                                             new sf::IntRect {0, 0, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}},
                    Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS