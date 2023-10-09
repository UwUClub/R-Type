#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::Bonus()
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        auto &world = Core::World::getInstance();

        display._elapsedTime += world.getDeltaTime();
        if (display._elapsedTime < 1) {
            return;
        }
        display.addEntity(
            ECS::Utils::Vector2f {static_cast<float>(SCREEN_WIDTH - BONUS_TEX_WIDTH),
                                  static_cast<float>(rand() % SCREEN_HEIGHT)},
            Component::Speed {BONUS_SPEED}, Component::TypeEntity {false, false, false, false, false, true, false},
            Component::LoadedSprite {BONUS_ASSET, nullptr, new SDL_Rect {0, 0, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT},
                                     new SDL_Rect {0, 0, BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}},
            Component::HitBox {BONUS_TEX_WIDTH, BONUS_TEX_HEIGHT}, Component::IsAlive {true, 0});
    }
} // namespace ECS