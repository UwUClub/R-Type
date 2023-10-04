#include <optional>
#include "../src/ecs/World.hpp"
#include "../src/rtype/components/Speed.hpp"
#include "../src/rtype/components/TypeEntity.hpp"
#include "catch2/catch_test_macros.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("World Test case 1", "[tag1]")
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    REQUIRE(world.isRunning() == true);
    world.stop();
    REQUIRE(world.isRunning() == false);
    world.start();
    REQUIRE(world.isRunning() == true);
}

TEST_CASE("World Test case 2", "[tag2]")
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &comp = world.registerComponent<Component::Speed>();
    auto entity = world.createEntity();

    world.addEntityComponent<Component::Speed>(entity, Component::Speed {10});

    REQUIRE(comp[entity]->speed == 10);
    // world.killEntity(entity);
    REQUIRE(comp[entity] == std::nullopt);
    world.removeComponent<Component::Speed>();
}

TEST_CASE("World Test case 3", "[tag3]")
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &comp = world.registerComponent<Component::Speed>();
    auto entity = world.createEntity();

    world.addEntityComponent<Component::Speed>(entity, Component::Speed {10});

    REQUIRE(comp[entity]->speed == 10);
    auto &comp2 = world.getComponent<Component::Speed>();
    REQUIRE(comp2[entity]->speed == 10);
    // world.killEntity(entity);
    REQUIRE(comp[entity] == std::nullopt);
    REQUIRE(comp2[entity] == std::nullopt);
    world.removeComponent<Component::Speed>();
}