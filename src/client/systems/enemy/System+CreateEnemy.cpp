#include <SFML/Graphics/Rect.hpp>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createEnemy()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_SPAWN) {
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent(event);
                    continue;
                }
                std::size_t onlineEntityId = static_cast<std::size_t>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1];
                float posY = gameEvent.getPayload()[2];

                AddEntity::addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {ENEMY_SPEED},
                    Component::TypeEntity {false, false, true, false, false, false, false, onlineEntityId},
                    Component::LoadedSprite {ENEMY_ASSET, nullptr,
                                             new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                             new sf::IntRect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}},
                    Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});

                eventManager->removeEvent(event);
            }
        }
    }

} // namespace ECS