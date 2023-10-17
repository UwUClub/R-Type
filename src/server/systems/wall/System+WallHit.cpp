#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::wallHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                         Core::SparseArray<Component::HitBox> &aHitBox, Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();

        for (size_t wallId = 0; wallId < aType.size(); wallId++) {
            if (!aType[wallId].has_value() || !aType[wallId].value().isWall) {
                continue;
            }
            for (size_t bullet = 0; bullet < aPos.size(); bullet++) {
                if (!aType[bullet].has_value() || !aType[bullet].value().isBullet) {
                    continue;
                }
                if (aPos[bullet].value().x > aPos[wallId].value().x
                    && aPos[bullet].value().x < aPos[wallId].value().x + aHitBox[wallId].value().width
                    && aPos[bullet].value().y > aPos[wallId].value().y
                    && aPos[bullet].value().y < aPos[wallId].value().y + aHitBox[wallId].value().height) {
                    aIsAlive[wallId].value().isAlive = false;
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS