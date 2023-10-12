#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveBackground(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto deltaTime = Core::World::getInstance().getDeltaTime();
        const auto size = aPos.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aPos[i].has_value() || !aType[i].value().isBackground) {
                continue;
            }
            aPos[i].value().x -= aSpeed[i].value().speed * deltaTime;
            if (aPos[i].value().x <= -SCREEN_WIDTH) {
                aPos[i].value().x = SCREEN_WIDTH;
            }
        }
    }
} // namespace ECS
