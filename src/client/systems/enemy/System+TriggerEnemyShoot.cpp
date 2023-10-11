#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerEnemyShoot(RType::ClientGameEvent *aEvent)
    {
        auto &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::ENEMY_SHOOT) {
            const auto payload = aEvent->getPayload();
            auto onlineMissileId = static_cast<std::size_t>(payload[0]);
            float posX = payload[1];
            auto posY = payload[2];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {MISSILES_SPEED},
                              Component::TypeEntity {false, false, false, true, false, false, false, onlineMissileId},
                              Component::LoadedSprite {MISSILES_ASSET, nullptr,
                                                       new SDL_Rect {304, 10, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                                                       new SDL_Rect {0, 0, MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT}},
                              Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT},
                              Component::IsAlive {false, 0});
        }
    }
} // namespace ECS
