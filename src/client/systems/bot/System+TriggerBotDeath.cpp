#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "SFMLDisplayClass.hpp"
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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        // Receive death event from server
        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::PLAYER_DEATH) {
                if (gameEvent.getPayload().size() != 1) {
                    eventManager->removeEvent(event);
                    continue;
                }

                size_t onlineBotId = static_cast<size_t>(gameEvent.getPayload()[0]);
                size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);
                if (!aIsAlive[localBotId].has_value()) {
                    eventManager->removeEvent(event);
                    continue;
                }

                aIsAlive[localBotId].value().isAlive = false;

                eventManager->removeEvent(event);
            }
        }

        // Explosion + entity removal
        for (size_t botId = 0; botId < aType.size(); botId++) {
            if (!aType[botId].has_value() || (!aType[botId].value().isBot && !aType[botId].value().isPlayer)) {
                continue;
            }
            if (!aIsAlive[botId].value().isAlive && aIsAlive[botId].value().timeToDie < 0) {
                std::cout << "Bot " << aType[botId].value().onlineId.value_or(0) << " killed" << std::endl;
                display.freeRects(botId);
                world.killEntity(botId);
            } else if (!aIsAlive[botId].value().isAlive && aIsAlive[botId].value().timeToDie == 0) {
                aSprites[botId].value().path = EXPLOSION_ASSET;
                aSprites[botId].value().texture = nullptr;
                aSprites[botId].value().rect->height = EXPLOSION_TEX_HEIGHT;
                aSprites[botId].value().rect->width = EXPLOSION_TEX_WIDTH;
                aSprites[botId].value().rect->left = 146;
                aSprites[botId].value().rect->top = 46;
                aIsAlive[botId].value().timeToDie = 1;
            } else if (!aIsAlive[botId].value().isAlive) {
                aIsAlive[botId].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
