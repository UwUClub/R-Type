#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveMissiles(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                              Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();

        for (size_t idx = 0; idx < aPos.size(); idx++) {
            if (!aPos[idx].has_value()) {
                continue;
            }
            auto &pos = aPos[idx].value();
            auto &speed = aSpeed[idx].value();
            auto &type = aType[idx].value();
            if (type.isBullet) {
                if (speed.speed == MISSILES_SPEED) {
                    pos.x -= speed.speed * world.getDeltaTime();
                } else if (speed.speed == BULLET_SPEED) {
                    pos.x += speed.speed * world.getDeltaTime();
                }
                if (pos.x > SCREEN_WIDTH + 30 || pos.x < -30) {
                    SDLDisplayClass::getInstance().freeRects(idx);
                    world.killEntity(idx);
                }
            }
        }
    }

} // namespace ECS
