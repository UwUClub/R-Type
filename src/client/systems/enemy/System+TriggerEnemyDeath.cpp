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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        // Receive death event from server
        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_DEATH) {
                if (gameEvent.getPayload().size() != 1) {
                    eventManager->removeEvent(event);
                    continue;
                }
                size_t onlineEnemyId = static_cast<size_t>(gameEvent.getPayload()[0]);
                size_t localEnemyId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineEnemyId);
                if (!aIsAlive[localEnemyId].has_value()) {
                    eventManager->removeEvent(event);
                    continue;
                }
                aIsAlive[localEnemyId].value().isAlive = false;

                eventManager->removeEvent(event);
            }
        }

        // Explosion + entity removal
        for (size_t enemy = 0; enemy < aType.size(); enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie < 0) {
                std::cout << "Enemy " << aType[enemy].value().onlineId.value_or(0) << " killed" << std::endl;
                display.freeRects(enemy);
                world.killEntity(enemy);
            } else if (!aIsAlive[enemy].value().isAlive && aIsAlive[enemy].value().timeToDie == 0) {
                aSprites[enemy].value().path = EXPLOSION_ASSET;
                aSprites[enemy].value().texture = nullptr;
                aSprites[enemy].value().rect->height = EXPLOSION_TEX_HEIGHT;
                aSprites[enemy].value().rect->width = EXPLOSION_TEX_WIDTH;
                aSprites[enemy].value().rect->top = 46;
                aSprites[enemy].value().rect->left = 146;
                aIsAlive[enemy].value().timeToDie = 1;
                if (rand() % 5 == 0) {
                    display.addEntity(
                        ECS::Utils::Vector2f {aPos[enemy].value().x, aPos[enemy].value().y},
                        Component::Speed {BONUS_SPEED},
                        Component::TypeEntity {false, false, false, false, false, true, false},
                        Component::LoadedSprite {BONUS_ASSET, nullptr,
                                                 new sf::IntRect {125, 520, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                                 new sf::IntRect {0, 0, 50, 50}, BONUS_SCALE},
                        Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}, Component::IsAlive {false, 0});
                }
            } else if (!aIsAlive[enemy].value().isAlive) {
                aIsAlive[enemy].value().timeToDie -= world.getDeltaTime();
            }
        }
    }
} // namespace ECS
