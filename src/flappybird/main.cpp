#include <iostream>
#include "Components.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include "System.hpp"
#include "Values.hpp"

int main(int ac, char **av)
{
    (void) ac;
    (void) av;

    // Load components
    ECS::Core::World &world = ECS::Core::World::getInstance();
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();

    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &speed = world.registerComponent<Component::Speed>();
    auto &type = world.registerComponent<Component::TypeEntity>();
    auto &jump = world.registerComponent<Component::Jump>();
    auto &score = world.registerComponent<Component::Score>();

    auto &renderConf = ECS::Render::RenderPluginConfig::getInstance();
    auto &physicConf = ECS::Physic::PhysicPluginConfig::getInstance();
    renderConf.load(CONFIG_PATH);
    physicConf.load(CONFIG_PATH);
    ECS::Render::RenderPlugin renderPlugin;
    ECS::Physic::PhysicPlugin physicPlugin;

    renderPlugin.plug(world, assetManager);
    physicPlugin.plug(world, assetManager);

    auto &sprite = world.getComponent<Component::LoadedSprite>();
    auto &weight = world.getComponent<Component::Weight>();
    auto &hitbox = world.getComponent<Component::HitBox>();
    auto &text = world.getComponent<Component::TextComponent>();

    // Load systems
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem(ECS::System::moveGround);
    world.addSystem(ECS::System::movePipes);
    world.addSystem(ECS::System::killBird);
    world.addSystem(ECS::System::updateScore);
    world.addSystem(ECS::System::replay);

    // Game loop
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    while (world.isRunning()) {
        world.runSystems();
        eventManager->keepEventsAndClear<>();
        world.calcDeltaTime();
    }
    return SUCCESS;
}