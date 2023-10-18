#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerEnemyDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::LoadedSprite> &aSprites,
                                   Core::SparseArray<Utils::Vector2f> &aPos)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
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
        for (auto &idx : toRemove) {
            eventManager->removeEvent<RType::ClientGameEvent>(idx);
        }

        // Explosion + entity removal
        const auto typeSize = aType.size();

        for (size_t enemy = 0; enemy < typeSize; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy || !aIsAlive[enemy].has_value()
                || !aSprites[enemy].has_value() || !aPos[enemy].has_value()) {
                continue;
            }

            auto &pos = aPos[enemy].value();
            auto &sprite = aSprites[enemy].value();
            auto &isAlive = aIsAlive[enemy].value();

            if (!isAlive.isAlive && isAlive.timeToDie < 0) {
                display.freeRects(enemy);
                world.killEntity(enemy);
            } else if (!isAlive.isAlive && isAlive.timeToDie == 0) {
                sprite.path = EXPLOSION_ASSET;
                sprite.texture = nullptr;
                sprite.rect->height = EXPLOSION_TEX_HEIGHT;
                sprite.rect->width = EXPLOSION_TEX_WIDTH;
                sprite.rect->top = 46;
                sprite.rect->left = 146;
                isAlive.timeToDie = 1;
                if (rand() % 5 == 0) {
                    display.addEntity(
                        ECS::Utils::Vector2f {pos.x, pos.y}, Component::Speed {BONUS_SPEED},
                        Component::TypeEntity {false, false, false, false, false, true, false},
                        Component::LoadedSprite {BONUS_ASSET, nullptr,
                                                 new sf::IntRect {125, 520, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                                 new sf::IntRect {0, 0, 50, 50}, BONUS_SCALE},
                        Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}, Component::IsAlive {false, 0});
                }
            } else if (!isAlive.isAlive) {
                isAlive.timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
