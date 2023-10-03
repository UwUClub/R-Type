#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::spawnEnemies()
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        auto &world = Core::World::getInstance();
        auto enemyTextureY = 0;
        auto enemyTextureX = 0;

        display._elapsedTime += world.getDeltaTime();
        if (display._elapsedTime < 1) {
            return;
        }
        display._elapsedTime = 0;
        display.addEntity(
            ECS::Utils::Vector2f {static_cast<float>(SCREEN_WIDTH - ENEMY_TEX_WIDTH),
                                  static_cast<float>(rand() % SCREEN_HEIGHT)},
            Component::Speed {ENEMY_SPEED}, Component::TypeEntity {false, true, false, false, false, false},
            Component::LoadedSprite {ENEMY_ASSET, nullptr,
                                     new SDL_Rect {enemyTextureX, enemyTextureY, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT},
                                     new SDL_Rect {0, 0, ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT}});
    }
} // namespace ECS
