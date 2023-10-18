#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveBackground(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto deltaTime = Core::World::getInstance().getDeltaTime();
        const auto size = aType.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aType[i].value().isBackground || !aPos[i].has_value()
                || !aSpeed[i].has_value()) {
                continue;
            }

            auto &pos = aPos[i].value();
            auto &speed = aSpeed[i].value().speed;

            pos.x -= speed * deltaTime;
            if (pos.x <= -SCREEN_WIDTH) {
                pos.x = SCREEN_WIDTH;
            }
        }
    }
} // namespace ECS
