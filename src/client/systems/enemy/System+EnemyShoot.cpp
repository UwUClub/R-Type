#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::enemyShoot()
    {
        auto &display = SDLDisplayClass::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ClientGameEvent &>(*event);

            if (gameEvent.getType() == RType::ClientEventType::ENEMY_SHOOT) {
                std::size_t onlineEntityId = static_cast<int>(gameEvent.getPayload()[0]);
                float posX = gameEvent.getPayload()[1] - MISSILES_TEX_WIDTH;
                auto posY = gameEvent.getPayload()[2] + ENEMY_TEX_HEIGHT / 2.0F - MISSILES_TEX_HEIGHT / 2.0F;

                display.addEntity(
                    ECS::Utils::Vector2f {posX, posY}, Component::Speed {MISSILES_SPEED},
                    Component::TypeEntity {false, false, false, true, false, false, false, onlineEntityId},
                    Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                             new SDL_Rect {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                             new SDL_Rect {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
                    Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}, Component::IsAlive {false, 0});
            }
        }
    }
} // namespace ECS