#include <SFML/Graphics/Rect.hpp>
#include <cstddef>
#include <vector>
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
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload();
            if (payload.size() != 5) {
                toRemove.push_back(i);
                continue;
            }

            size_t onlineEntityId = static_cast<int>(payload[0]);
            Component::TypeEntity entityType {false, true, false, false, false, false, false, onlineEntityId};
            bool isLocalPlayer = payload[1] == 1;

            if (isLocalPlayer) {
                entityType.isPlayer = true;
                entityType.isBot = false;
            }

            int color = static_cast<int>(payload[2]);
            float posX = payload[3];
            float posY = payload[4];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {PLAYER_SPEED}, entityType,
                              Component::LoadedSprite {
                                  PLAYER_ASSET, nullptr,
                                  new sf::IntRect {0, color * PLAYER_TEX_HEIGHT, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                  new sf::IntRect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}},
                              Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}, Component::IsAlive {true, 0});
            toRemove.push_back(i);
        }
        for (auto &idx : toRemove) {
            eventManager->removeEvent<RType::ClientGameEvent>(idx);
        }
    }

} // namespace ECS