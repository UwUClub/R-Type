#include <iostream>
#include "SFMLDisplayClass.hpp"
#include "SparseArray.hpp"
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

        for (size_t player = 0; player < size; player++) {
            if (!aType[player].has_value() || !aType[player].value().isPlayer || !aPos[player].has_value()
                || !aHitBox[player].has_value()) {
                continue;
            }

            auto &posPlayer = aPos[player].value();
            auto &hitBoxPlayer = aHitBox[player].value();
            const auto missileSize = aPos.size();

            for (size_t missileId = 0; missileId < missileSize; missileId++) {
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
