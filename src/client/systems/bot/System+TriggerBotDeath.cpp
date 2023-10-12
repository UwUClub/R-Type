#include "ClientGameEvent.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::triggerBotDeath(RType::ClientGameEvent *aEvent)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &isAliveComp = world.getComponent<Component::IsAlive>();
        auto &spriteComp = world.getComponent<Component::LoadedSprite>();
        auto &aType = world.getComponent<Component::TypeEntity>();
        const auto size = aType.size();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_DEATH) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 1) {
                return;
            }
            auto onlineBotId = static_cast<size_t>(payload[0]);
            std::size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(typeComp, onlineBotId);

            if (isAliveComp[localBotId].has_value()) {
                isAliveComp[localBotId].value().isAlive = false;
            }
        }

        // Explosion + entity removal
        for (size_t botId = 0; botId < size; botId++) {
            if (!aType[botId].has_value() || isAliveComp[botId].has_value() || !spriteComp[botId].has_value()
                || (!aType[botId].value().isBot && !aType[botId].value().isPlayer)) {
                continue;
            }
            if (!isAliveComp[botId].value().isAlive && isAliveComp[botId].value().timeToDie < 0) {
                display.freeRects(botId);
                world.killEntity(botId);
                continue;
            }
            if (!isAliveComp[botId].value().isAlive && isAliveComp[botId].value().timeToDie == 0) {
                spriteComp[botId].value().path = EXPLOSION_ASSET;
                spriteComp[botId].value().texture = nullptr;
                spriteComp[botId].value().rect->h = EXPLOSION_TEX_HEIGHT;
                spriteComp[botId].value().rect->w = EXPLOSION_TEX_WIDTH;
                spriteComp[botId].value().rect->x = 146;
                spriteComp[botId].value().rect->y = 46;
                isAliveComp[botId].value().timeToDie = 1;
                continue;
            }
            if (!isAliveComp[botId].value().isAlive) {
                isAliveComp[botId].value().timeToDie -= world.getDeltaTime();
                continue;
            }
        }
    }
} // namespace ECS
