#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::enemyHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();
        const auto size = aPos.size();

        for (std::size_t enemy = 0; enemy < size; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }
            for (std::size_t bullet = 0; bullet < size; bullet++) {
                if (!aType[bullet].has_value() || !aPos[bullet].has_value() || !aHitBox[enemy].has_value()
                    || !aType[bullet].value().isBullet) {
                    continue;
                }
                if (aPos[bullet].value().x > aPos[enemy].value().x
                    && aPos[bullet].value().x < aPos[enemy].value().x + aHitBox[enemy].value().width
                    && aPos[bullet].value().y > aPos[enemy].value().y
                    && aPos[bullet].value().y < aPos[enemy].value().y + aHitBox[enemy].value().height) {
                    display.freeRects(bullet);
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS
