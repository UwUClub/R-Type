#include <iostream>
#include "ClientGameEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::createServerFullErrorMessage(RType::ClientGameEvent *aEvent)
    {
        auto &world = ECS::Core::World::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::SERVER_FULL) {
            display.freeRects(0);
            world.killEntity(0);
            display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - SERVER_FULL_MESSAGE_TEX_WIDTH / 2,
                                                    SCREEN_HEIGHT / 2 - SERVER_FULL_MESSAGE_TEX_HEIGHT / 2},
                              Component::Speed {0},
                              Component::TypeEntity {false, false, false, false, false, false, true},
                              Component::LoadedSprite {SERVER_FULL_MESSAGE, nullptr, nullptr,
                                                       new SDL_Rect {400, 15, SERVER_FULL_MESSAGE_TEX_WIDTH,
                                                                     SERVER_FULL_MESSAGE_TEX_HEIGHT}},
                              Component::HitBox {}, Component::IsAlive {false, 0});
        }
    }
} // namespace ECS
