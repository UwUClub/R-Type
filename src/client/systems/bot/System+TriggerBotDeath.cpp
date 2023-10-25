#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "IsAlive.hpp"
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

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 1) {
                toRemove.push_back(i);
                continue;
            }

            auto onlineBotId = static_cast<size_t>(payload[0]);
            size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);

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

            if (!isAlive.isAlive && isAlive.timeToDie < 0) {
                world.killEntity(botId);
            } else if (!isAlive.isAlive && isAlive.timeToDie == 0) {
                sprite.path = EXPLOSION_ASSET;
                sprite.texture = nullptr;
                sprite.rect.height = EXPLOSION_TEX_HEIGHT;
                sprite.rect.width = EXPLOSION_TEX_WIDTH;
                sprite.rect.left = 146;
                sprite.rect.top = 46;
                isAlive.timeToDie = 1;
            } else if (!isAlive.isAlive) {
                isAlive.timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
