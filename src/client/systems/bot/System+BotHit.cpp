#include <iostream>
#include "EwECS/SparseArray.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "components/HitBox.hpp"
#include "components/IsAlive.hpp"

namespace ECS {
    void System::botHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                        Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        const auto size = aType.size();

        for (unsigned short player = 0; player < size; player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer || !aPos[player].has_value()
                || !aHitBox[player].has_value()) {
                continue;
            }

            auto &posPlayer = aPos[player].value();
            auto &hitBoxPlayer = aHitBox[player].value();
            const auto missileSize = aPos.size();

            for (unsigned short missileId = 0; missileId < missileSize; missileId++) {
                if (!aType[missileId].has_value() || !aType[missileId].value().isBullet
                    || !aPos[missileId].has_value()) {
                    continue;
                }
                auto &posMissile = aPos[missileId].value();
                if ((posMissile.x > posPlayer.x && posMissile.x < posPlayer.x + hitBoxPlayer.width
                     && posMissile.y > posPlayer.y && posMissile.y < posPlayer.y + hitBoxPlayer.height)) {
                    display.freeRects(missileId);
                    world.killEntity(missileId);
                }
            }
        }
    }
} // namespace ECS
