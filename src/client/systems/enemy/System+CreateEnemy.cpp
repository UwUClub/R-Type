#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createEnemy(RType::ClientGameEvent *aEvent)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::ENEMY_SPAWN) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 3) {
                return;
            }
            auto onlineEntityId = static_cast<std::size_t>(payload[0]);
            float posX = payload[1];
            float posY = payload[2];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {ENEMY_SPEED},
                              Component::TypeEntity {false, false, true, false, false, false, false, onlineEntityId},
                              Component::LoadedSprite {ENEMY_ASSET, nullptr,
                                                       new SDL_Rect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                                       new SDL_Rect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}},
                              Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}, Component::IsAlive {true, 0});
        }
    }
} // namespace ECS
