#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveBackground(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                Core::SparseArray<Component::TypeEntity> &aType)
    {
        for (size_t i = 0; i < aType.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isBackground) {
                continue;
            }
            aPos[i].value().x -= aSpeed[i].value().speed;
            if (aPos[i].value().x <= -SCREEN_WIDTH) {
                aPos[i].value().x = SCREEN_WIDTH;
            }
        }
    }
} // namespace ECS