#include <iostream>
#include "ClientGameEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::createBackground(RType::ClientGameEvent *aEvent)
    {
        auto &world = ECS::Core::World::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_SPAWN) {
            const auto payload = aEvent->getPayload();
            bool isLocalPlayer = payload[1] == 1;

            if (isLocalPlayer) {
                display.freeRects(0);
                world.killEntity(0);
                display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                                  Component::TypeEntity {false, false, false, false, false, false, true},
                                  Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                           new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                  Component::HitBox {}, Component::IsAlive {false, 0});
                display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                                  Component::TypeEntity {false, false, false, false, false, false, true},
                                  Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                           new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                                  Component::HitBox {}, Component::IsAlive {false, 0});
            }
        }
    }
} // namespace ECS
