#include <iostream>
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::applyGravity(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Weight> &aWeight)
    {
        auto &world = Core::World::getInstance();

        for (size_t i = 0; i < aWeight.size(); i++) {
            if (!aWeight[i].has_value() || !aPos[i].has_value()) {
                continue;
            }
            std::cout << aPos[i].value().y << std::endl;
            aPos[i].value().y += (aWeight[i].value().weight - aPos[i].value().y) * world.getDeltaTime();
        }
    }

} // namespace ECS
