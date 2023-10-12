#include <cstddef>
#include "ClientGameEvent.hpp"
#include "IsAlive.hpp"
#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::triggerBotShoot(RType::ClientGameEvent *aEvent)
    {
        auto &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_SHOOT) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 3) {
                return;
            }
            auto onlineBulletId = static_cast<std::size_t>(payload[0]);
            float posX = payload[1];
            auto posY = payload[2];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {BULLET_SPEED},
                              Component::TypeEntity {false, false, false, true, false, false, false, onlineBulletId},
                              Component::LoadedSprite {BULLET_ASSET, nullptr,
                                                       new SDL_Rect {207, 10, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT},
                                                       new SDL_Rect {0, 0, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}},
                              Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});
        }
    }
} // namespace ECS
