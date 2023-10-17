#include <SFML/Graphics/Rect.hpp>
#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createBot()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_SPAWN) {
                if (gameEvent.getPayload().size() != 5) {
                    eventManager->removeEvent(event);
                    continue;
                }

                size_t onlineEntityId = static_cast<int>(gameEvent.getPayload()[0]);
                Component::TypeEntity entityType {false, true, false, false, false, false, false, onlineEntityId};

                bool isLocalPlayer = gameEvent.getPayload()[1] == 1;
                if (isLocalPlayer) {
                    entityType.isPlayer = true;
                    entityType.isBot = false;
                }

                int color = static_cast<int>(gameEvent.getPayload()[2]);
                float posX = gameEvent.getPayload()[3];
                float posY = gameEvent.getPayload()[4];
                std::cout << "Player with color " << color << " joined" << std::endl;

                display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {PLAYER_SPEED}, entityType,
                                  Component::LoadedSprite {
                                      PLAYER_ASSET, nullptr,
                                      new sf::IntRect {0, color * PLAYER_TEX_HEIGHT, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                      new sf::IntRect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}},
                                  Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                  Component::IsAlive {true, 0});

                eventManager->removeEvent(event);
            }
        }
    }

} // namespace ECS