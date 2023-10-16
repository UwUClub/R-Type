#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "RayDisplayClass.hpp"
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
        auto &display = RayDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();

        // Receive death event from server
        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_DEATH) {
                if (gameEvent.getPayload().size() != 1) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                size_t onlineEnemyId = static_cast<size_t>(gameEvent.getPayload()[0]);
                size_t localEnemyId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineEnemyId);
                if (!aIsAlive[localEnemyId].has_value()) {
                    eventManager->removeEvent<RType::ClientGameEvent>(i);
                    continue;
                }
                aIsAlive[localEnemyId].value().isAlive = false;

                eventManager->removeEvent<RType::ClientGameEvent>(i);
            }
        }

        // Explosion + entity removal
        for (size_t enemy = 0; enemy < aType.size(); enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie < 0) {
                std::cout << "Enemy " << aType[enemy].value().onlineId.value_or(0) << " killed" << std::endl;
                world.killEntity(enemy);
            } else if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie == 0) {
                aSprites[enemy].value().path = EXPLOSION_ASSET;
                aSprites[enemy].value().texture = nullptr;
                aSprites[enemy].value().rect.height = EXPLOSION_TEX_HEIGHT;
                aSprites[enemy].value().rect.width = EXPLOSION_TEX_WIDTH;
                aSprites[enemy].value().rect.x = 146;
                aSprites[enemy].value().rect.y = 46;
                aIsAlive[enemy].value().timeToDie = 1;
                if (rand() % 5 == 0) {
                    display.addEntity(ECS::Utils::Vector2f {aPos[enemy].value().x, aPos[enemy].value().y},
                                      Component::Speed {BONUS_SPEED},
                                      Component::TypeEntity {false, false, false, false, false, true, false},
                                      Component::LoadedSprite {BONUS_ASSET, nullptr,
                                                               Rectangle {125, 520, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                                               Rectangle {0, 0, 50, 50}},
                                      Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                      Component::IsAlive {false, 0});
                }
            } else if (!aIsAlive[enemy].value().isAlive) {
                aIsAlive[enemy].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
