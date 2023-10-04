#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::destroyEnemy(Core::SparseArray<Utils::Vector2f> &aPos,
                              Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::HitBox> &aHitBox,
                              Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t enemy = 0; enemy < aType.size(); enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            for (size_t bullet = 0; bullet < aPos.size(); bullet++) {
                if (!aType[bullet].has_value() || !aType[bullet].value().isBullet) {
                    continue;
                }
                if (aPos[bullet].value().x > aPos[enemy].value().x
                    && aPos[bullet].value().x < aPos[enemy].value().x + aHitBox[enemy].value().width
                    && aPos[bullet].value().y > aPos[enemy].value().y
                    && aPos[bullet].value().y < aPos[enemy].value().y + aHitBox[enemy].value().height) {
                    aIsAlive[enemy].value().isAlive = false;
                    display.freeRects(bullet);
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS