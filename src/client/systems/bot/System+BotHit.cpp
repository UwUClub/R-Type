#include <iostream>
#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::botHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                        Core::SparseArray<Component::IsAlive> &aIsAlive, Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();

        for (size_t player = 0; player < aType.size(); player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer) {
                continue;
            }
            for (size_t missileId = 0; missileId < aPos.size(); missileId++) {
                if (!aType[missileId].has_value() || !aType[missileId].value().isBullet) {
                    continue;
                }
                if ((aPos[missileId].value().x > aPos[player].value().x
                     && aPos[missileId].value().x < aPos[player].value().x + aHitBox[player].value().width
                     && aPos[missileId].value().y > aPos[player].value().y
                     && aPos[missileId].value().y < aPos[player].value().y + aHitBox[player].value().height)) {
                    display.freeRects(missileId);
                    world.killEntity(missileId);
                }
            }
        }
    }
} // namespace ECS
