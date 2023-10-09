#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox,
                          Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();

        for (size_t enemyId = 0; enemyId < aType.size(); enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy) {
                continue;
            }
            for (size_t bullet = 0; bullet < aPos.size(); bullet++) {
                if (!aType[bullet].has_value() || !aType[bullet].value().isBullet) {
                    continue;
                }
                if (aPos[bullet].value().x > aPos[enemyId].value().x
                    && aPos[bullet].value().x < aPos[enemyId].value().x + aHitBox[enemyId].value().width
                    && aPos[bullet].value().y > aPos[enemyId].value().y
                    && aPos[bullet].value().y < aPos[enemyId].value().y + aHitBox[enemyId].value().height) {
                    aIsAlive[enemyId].value().isAlive = false;
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS