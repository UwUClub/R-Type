#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "WindowEvent.hpp"

namespace ECS {
    void System::spawnEnemies(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                              Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        auto &world = Core::World::getInstance();

        display._elapsedTime += world.getDeltaTime();
        if (display._elapsedTime < 1)
            return;
        display._elapsedTime = 0;
        display.addEntity(
            ECS::Utils::Vector2f {static_cast<float>(SCREEN_WIDTH - 30), static_cast<float>(rand() % SCREEN_HEIGHT)},
            Component::Speed {20}, Component::TypeEntity {false, true, false, false, false, false},
            Component::LoadedSprite {PLAYER_ASSET, nullptr, new SDL_Rect {0, 0, 33, 17}, new SDL_Rect {0, 0, 33, 17}});
    }
} // namespace ECS