#include <cstddef>
#include <vector>
#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createBot()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_SPAWN) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerJoinedPayload>();

            Component::TypeEntity entityType {false, true, false, false, false, false, false, payload.playerId, false};

            if (payload.isReceiver) {
                entityType.isPlayer = true;
                entityType.isBot = false;
            }

            std::string path = "config/player_" + std::to_string(payload.playerColor + 1) + ".json";

            try {
                AddEntity::addEntity(ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {PLAYER_SPEED},
                                     entityType, Component::LoadedSprite {path},
                                     Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                     Component::IsAlive {true, 0});
            } catch (const std::exception &e) {
                ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
