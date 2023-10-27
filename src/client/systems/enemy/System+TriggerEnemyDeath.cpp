#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"

namespace ECS {
    void System::triggerEnemyDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::LoadedSprite> &aSprites,
                                   Core::SparseArray<Utils::Vector2f> &aPos)
    {
        auto &world = Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        // Receive death event from server
        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::ENEMY_DEATH) {
                continue;
            }

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 1) {
                toRemove.push_back(i);
                continue;
            }

            auto onlineEnemyId = static_cast<size_t>(payload[0]);
            size_t localEnemyId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineEnemyId);

            if (!aIsAlive[localEnemyId].has_value()) {
                toRemove.push_back(i);
                continue;
            }
            aIsAlive[localEnemyId].value().isAlive = false;
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);

        // Explosion + entity removal
        const auto typeSize = aType.size();

        for (size_t enemy = 0; enemy < typeSize; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy || !aIsAlive[enemy].has_value()
                || !aSprites[enemy].has_value() || !aPos[enemy].has_value()) {
                continue;
            }

            auto &sprite = aSprites[enemy].value();
            auto &isAlive = aIsAlive[enemy].value();

            if (!isAlive.isAlive && isAlive.timeToDie < 0) {
                world.killEntity(enemy);
            } else if (!isAlive.isAlive && isAlive.timeToDie == 0) {
                sprite.path = EXPLOSION_ASSET;
                sprite.texture = nullptr;
                for (size_t i = 0; i < sprite.rect.size(); i++) {
                    sprite.rect[i].height = EXPLOSION_TEX_HEIGHT;
                    sprite.rect[i].width = EXPLOSION_TEX_WIDTH;
                    sprite.rect[i].left = 146 * (i + 1);
                    sprite.rect[i].top = 46;
                    sprite.rectTime[i] = 0.2;
                }
                isAlive.timeToDie = 1;
                if (rand() % 5 == 0) {
                    AddEntity::addEntity(ECS::Utils::Vector2f {aPos[enemy].value().x, aPos[enemy].value().y},
                                         Component::Speed {BONUS_SPEED},
                                         Component::TypeEntity {false, false, false, false, false, true, false},
                                         Component::LoadedSprite {"config/bonus.json"},
                                         Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                         Component::IsAlive {false, 0});
                }
            } else if (!isAlive.isAlive) {
                isAlive.timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
