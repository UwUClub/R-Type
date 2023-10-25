#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox,
                          Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        auto &world = Core::World::getInstance();
        const auto size = aType.size();

        for (size_t enemyId = 0; enemyId < size; enemyId++) {
            if (!aType[enemyId].has_value() || !aType[enemyId].value().isEnemy || !aPos[enemyId].has_value()
                || !aHitBox[enemyId].has_value() || !aIsAlive[enemyId].has_value()) {
                continue;
            }

            auto &posEnemy = aPos[enemyId].value();
            auto &hitBoxEnemy = aHitBox[enemyId].value();
            const auto posSize = aPos.size();

            for (size_t bullet = 0; bullet < posSize; bullet++) {
                if (!aType[bullet].has_value() || !aType[bullet].value().isBullet || !aPos[bullet].has_value()) {
                    continue;
                }

                auto &posBullet = aPos[bullet].value();

                if (posBullet.x > posEnemy.x && posBullet.x < posEnemy.x + hitBoxEnemy.width && posBullet.y > posEnemy.y
                    && posBullet.y < posEnemy.y + hitBoxEnemy.height) {
                    aIsAlive[enemyId].value().isAlive = false;
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS
