#include <iostream>
#include "World.hpp"
#include "Utils.hpp"
#include "System.hpp"

int main()
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &spd = world.registerComponent<ECS::Utils::Speed>();
    auto &type = world.registerComponent<ECS::Utils::TypeEntity>();

    size_t idPlayer = world.createEntity();

    vec.insertAt(idPlayer, ECS::Utils::Vector2f{10, 10});
    spd.insertAt(idPlayer, ECS::Utils::Speed{10});
    type.insertAt(idPlayer, ECS::Utils::TypeEntity{true, false, false, false, false});
    world.addSystem<ECS::Utils::Vector2f, ECS::Utils::Speed, ECS::Utils::TypeEntity>(ECS::System::movePlayer);
    world.runSystems();
    std::cout << vec[idPlayer].value().x << std::endl;
    std::cout << vec[idPlayer].value().y << std::endl;
    return 0;
}