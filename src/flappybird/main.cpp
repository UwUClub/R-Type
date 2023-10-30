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

    // Load config
    ConfigReader &configReader = ConfigReader::getInstance();
    auto &conf = configReader.loadConfig(CONFIG_PATH);
    auto &backgroundConf = conf["entities"]["background"];
    auto &ground1Conf = conf["entities"]["ground_1"];
    auto &ground2Conf = conf["entities"]["ground_2"];
    auto &birdConf = conf["entities"]["bird"];

    // Load components
    ECS::Core::World &world = ECS::Core::World::getInstance();
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();

    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &speed = world.registerComponent<Component::Speed>();
    auto &type = world.registerComponent<Component::TypeEntity>();
    auto &jump = world.registerComponent<Component::Jump>();

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

    // Setup background
    size_t backgroundId = world.createEntity();
    vec.insertAt(backgroundId, ECS::Utils::Vector2f {0, 0});
    type.insertAt(backgroundId, Component::TypeEntity {EntityType::BACKGROUND});
    sprite.insertAt(backgroundId, Component::LoadedSprite {"config/flappybird/background.json"});

    // Setup ground entities
    size_t ground1Id = world.createEntity();
    vec.insertAt(ground1Id, ECS::Utils::Vector2f {0, ground1Conf["position"]["y"]});
    speed.insertAt(ground1Id, Component::Speed {ground1Conf["speed"]});
    type.insertAt(ground1Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground1Id, Component::LoadedSprite {"config/flappybird/ground.json"});

    size_t ground2Id = world.createEntity();
    vec.insertAt(ground2Id, ECS::Utils::Vector2f {ground2Conf["position"]["x"], ground2Conf["position"]["y"]});
    speed.insertAt(ground2Id, Component::Speed {ground2Conf["speed"]});
    type.insertAt(ground2Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground2Id, Component::LoadedSprite {"config/flappybird/ground.json"});

    // Setup player entity
    size_t birdId = world.createEntity();
    vec.insertAt(birdId, ECS::Utils::Vector2f {birdConf["position"]["x"], birdConf["position"]["y"]});
    type.insertAt(birdId, Component::TypeEntity {EntityType::BIRD});
    sprite.insertAt(birdId, Component::LoadedSprite {"config/flappybird/bird.json"});
    weight.insertAt(birdId, Component::Weight(birdConf["weight"], physicConf._initialJumpVelocity));
    jump.insertAt(birdId, Component::Jump(birdConf["jump"]["strength"], birdConf["jump"]["height"],
                                          birdConf["jump"]["floating"]));

    // Setup pipes
    size_t pipeId = world.createEntity();
    type.insertAt(pipeId, Component::TypeEntity {EntityType::PIPE});
    sprite.insertAt(pipeId, Component::LoadedSprite {"config/flappybird/pipe.json"});
    vec.insertAt(pipeId, ECS::Utils::Vector2f {0, 0});

    // Load systems
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveGround);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::killOnTouch);
    //    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::killOnPipe);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::displayScore);

    // Game loop
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    while (world.isRunning()) {
        world.runSystems();
        eventManager->keepEventsAndClear<>();
        world.calcDeltaTime();
    }
    return SUCCESS;
}