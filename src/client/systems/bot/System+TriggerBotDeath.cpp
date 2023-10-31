#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "IsAlive.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"

namespace ECS {
    void System::triggerBotDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                 Core::SparseArray<Component::IsAlive> &aIsAlive,
                                 Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;

        // Receive death event from server
        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_DEATH) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerDiedPayload>();

            const auto localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, payload.playerId);

            if (!aIsAlive[localBotId].has_value()) {
                toRemove.push_back(i);
                continue;
            }

            aIsAlive[localBotId].value().isAlive = false;

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);

        // Explosion + entity removal
        const auto size = aType.size();

        for (size_t botId = 0; botId < size; botId++) {
            if (!aType[botId].has_value() || (!aType[botId].value().isBot && !aType[botId].value().isPlayer)
                || !aIsAlive[botId].has_value() || !aSprites[botId].has_value()) {
                continue;
            }

            auto &sprite = aSprites[botId].value();
            auto &isAlive = aIsAlive[botId].value();
            auto &type = aType[botId].value();

            if (!isAlive.isAlive && isAlive.timeToDie < 0) {
                world.killEntity(botId);
            } else if (!isAlive.isAlive && isAlive.timeToDie == 0) {
                sprite.path = EXPLOSION_ASSET;
                sprite.texture = nullptr;
                type.isBot = true;
                type.isPlayer = false;
                for (size_t i = 0; i < sprite.rect.size(); i++) {
                    sprite.rect[i].height = EXPLOSION_TEX_HEIGHT;
                    sprite.rect[i].width = EXPLOSION_TEX_WIDTH;
                    sprite.rect[i].left = 146 * (i + 1);
                    sprite.rect[i].top = 46;
                    sprite.rectTime[i] = 0.2;
                }
                isAlive.timeToDie = 1;
            } else if (!isAlive.isAlive) {
                isAlive.timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
