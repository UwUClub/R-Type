#include <SFML/Graphics/Rect.hpp>
#include <cstddef>
#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
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

        for (unsigned short i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerJoinedPayload>();

            Component::TypeEntity entityType {false, true, false, false, false, false, false, payload.playerId};

            if (payload.isReceiver) {
                entityType.isPlayer = true;
                entityType.isBot = false;
            }

            display.addEntity(ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {PLAYER_SPEED},
                              entityType,
                              Component::LoadedSprite {PLAYER_ASSET, nullptr,
                                                       new sf::IntRect {0, payload.playerColor * PLAYER_TEX_HEIGHT,
                                                                        PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                                       new sf::IntRect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}},
                              Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}, Component::IsAlive {true, 0});
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS