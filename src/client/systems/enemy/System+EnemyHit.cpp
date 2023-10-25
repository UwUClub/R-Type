#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyHit(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                          Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        const auto size = aType.size();

        for (unsigned short enemy = 0; enemy < size; enemy++) {
            if (!aType[enemy].has_value() || !aType[enemy].value().isEnemy) {
                continue;
            }

            auto &posEnemy = aPos[enemy].value();
            auto &hitBoxEnemy = aHitBox[enemy].value();
            const auto size = aPos.size();

            for (unsigned short bullet = 0; bullet < size; bullet++) {
                if (!aType[bullet].has_value() || !aType[bullet].value().isBullet || !aPos[bullet].has_value()) {
                    continue;
                }

                auto &posBullet = aPos[bullet].value();

                if (posBullet.x > posEnemy.x && posBullet.x < posEnemy.x + hitBoxEnemy.width && posBullet.y > posEnemy.y
                    && posBullet.y < posEnemy.y + hitBoxEnemy.height) {
                    display.freeRects(bullet);
                    world.killEntity(bullet);
                    break;
                }
            }
        }
    }
} // namespace ECS