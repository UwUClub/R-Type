#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "WindowEvent.hpp"

namespace ECS {
    void System::spawnEnemies()
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        auto &world = Core::World::getInstance();

        display._elapsedTime += world.getDeltaTime();
        if (display._elapsedTime < 1)
            return;
        display._elapsedTime = 0;
        display.addEntity(
            ECS::Utils::Vector2f {static_cast<float>(SCREEN_WIDTH), static_cast<float>(rand() % SCREEN_HEIGHT)},
            Component::Speed {20}, Component::TypeEntity {false, true, false, false, false, false},
            Component::LoadedSprite {ENEMY_ASSET, nullptr, new SDL_Rect {0, 0, 33, 33}, new SDL_Rect {0, 0, 33, 33}});
    }
} // namespace ECS
