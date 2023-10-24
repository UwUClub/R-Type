#include "../System.hpp"
#include "EwECS/World.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "Values.hpp"

namespace ECS {
    void System::moveBonus(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                           Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        const auto size = aType.size();

        for (size_t idx = 0; idx < size; idx++) {
            if (!aPos[idx].has_value() || !aSpeed[idx].has_value() || !aType[idx].has_value()) {
                continue;
            }

            auto &pos = aPos[idx].value();
            auto &speed = aSpeed[idx].value();
            auto &type = aType[idx].value();

            if (type.isBonus) {
                pos.x -= speed.speed * world.getDeltaTime();
                if (pos.x < -30) {
                    world.killEntity(idx);
                }
            }
        }
    }

} // namespace ECS
