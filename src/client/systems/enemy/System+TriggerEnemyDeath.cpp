#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"
#include "World.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::triggerEnemyDeath(RType::ClientGameEvent *aEvent)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &isAliveComp = world.getComponent<Component::IsAlive>();
        auto &spriteComp = world.getComponent<Component::LoadedSprite>();
        auto &posComp = world.getComponent<Utils::Vector2f>();
        const auto size = typeComp.size();

        if (aEvent->getType() == RType::ClientEventType::ENEMY_DEATH) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 1) {
                return;
            }
            auto onlineEnemyId = static_cast<size_t>(payload[0]);
            std::size_t localEnemyId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(typeComp, onlineEnemyId);
            if (isAliveComp[localEnemyId].has_value()) {
                isAliveComp[localEnemyId].value().isAlive = false;
            }
        }

        // Explosion + entity removal
        for (std::size_t enemy = 0; enemy < size; enemy++) {
            if (!typeComp[enemy].has_value() || !isAliveComp[enemy].has_value() || !typeComp[enemy].value().isEnemy) {
                continue;
            }
            if (!isAliveComp[enemy].value().isAlive && isAliveComp[enemy].value().timeToDie < 0) {
                display.freeRects(enemy);
                world.killEntity(enemy);
                continue;
            }
            if (!isAliveComp[enemy].value().isAlive && isAliveComp[enemy].value().timeToDie == 0) {
                spriteComp[enemy].value().path = EXPLOSION_ASSET;
                spriteComp[enemy].value().texture = nullptr;
                spriteComp[enemy].value().rect->h = EXPLOSION_TEX_HEIGHT;
                spriteComp[enemy].value().rect->w = EXPLOSION_TEX_WIDTH;
                spriteComp[enemy].value().rect->x = 146;
                spriteComp[enemy].value().rect->y = 46;
                isAliveComp[enemy].value().timeToDie = 1;
                if (rand() % 5 == 0) {
                    display.addEntity(
                        ECS::Utils::Vector2f {posComp[enemy].value().x, posComp[enemy].value().y},
                        Component::Speed {BONUS_SPEED},
                        Component::TypeEntity {false, false, false, false, false, true, false},
                        Component::LoadedSprite {BONUS_ASSET, nullptr,
                                                 new SDL_Rect {125, 520, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                                 new SDL_Rect {0, 0, 50, 50}},
                        Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}, Component::IsAlive {false, 0});
                }
                continue;
            }
            if (!isAliveComp[enemy].value().isAlive) {
                isAliveComp[enemy].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
