#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::killPlayer(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t player = 0; player < aType.size(); player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer) {
                continue;
            }
            for (size_t obstacle = 0; obstacle < aPos.size(); obstacle++) {
                if (!aType[obstacle].has_value() || aType[obstacle].value().isBonus
                    || aType[obstacle].value().isPlayer) {
                    continue;
                }
                if ((aPos[player].value().x > aPos[obstacle].value().x
                    && aPos[player].value().x < aPos[obstacle].value().x + aHitBox[obstacle].value().width
                    && aPos[player].value().y > aPos[obstacle].value().y
                    && aPos[player].value().y < aPos[obstacle].value().y + aHitBox[obstacle].value().height)
                    || (aPos[player].value().x + aHitBox[player].value().width > aPos[obstacle].value().x
                    && aPos[player].value().x + aHitBox[player].value().width < aPos[obstacle].value().x + aHitBox[obstacle].value().width
                    && aPos[player].value().y > aPos[obstacle].value().y
                    && aPos[player].value().y < aPos[obstacle].value().y + aHitBox[obstacle].value().height)) {
                    aIsAlive[player].value().isAlive = false;
                    if (aType[obstacle].value().isBullet) {
                        display.freeRects(obstacle);
                        world.killEntity(obstacle);
                    }
                    break;
                }
            }
        }
    }
} // namespace ECS
