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
    auto &scoreConf = conf["entities"]["score"];
    auto &ground1Conf = conf["entities"]["ground_1"];
    auto &ground2Conf = conf["entities"]["ground_2"];
    auto &birdConf = conf["entities"]["bird"];
    auto &pipe1Conf = conf["entities"]["pipe_1"];

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

    // Setup background
    size_t backgroundId = world.createEntity();
    vec.insertAt(backgroundId, ECS::Utils::Vector2f {0, 0});
    type.insertAt(backgroundId, Component::TypeEntity {EntityType::BACKGROUND});
    sprite.insertAt(backgroundId, Component::LoadedSprite {"config/flappybird/sprites/background.json"});

    // Setup score entity
    size_t scoreId = world.createEntity();
    vec.insertAt(scoreId, ECS::Utils::Vector2f {scoreConf["position"]["x"], scoreConf["position"]["y"]});
    type.insertAt(scoreId, Component::TypeEntity {EntityType::TEXT});
    score.insertAt(scoreId, Component::Score {0});
    text.insertAt(scoreId, Component::TextComponent("0", Component::TextColor::WHITE, scoreConf["size"]));

    // Setup pipes
    size_t pipe1Id = world.createEntity();
    vec.insertAt(pipe1Id, ECS::Utils::Vector2f {pipe1Conf["position"]["x"], pipe1Conf["position"]["y"]});
    speed.insertAt(pipe1Id, Component::Speed {pipe1Conf["speed"]});
    type.insertAt(pipe1Id, Component::TypeEntity {EntityType::PIPE});
    sprite.insertAt(pipe1Id, Component::LoadedSprite {"config/flappybird/sprites/pipe.json"});
    hitbox.insertAt(pipe1Id, Component::HitBox {pipe1Conf["hitbox"]["width"], pipe1Conf["hitbox"]["height"]});
    score.insertAt(pipe1Id, Component::Score {0});

    // Setup ground entities
    size_t ground1Id = world.createEntity();
    vec.insertAt(ground1Id, ECS::Utils::Vector2f {0, ground1Conf["position"]["y"]});
    speed.insertAt(ground1Id, Component::Speed {ground1Conf["speed"]});
    type.insertAt(ground1Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground1Id, Component::LoadedSprite {"config/flappybird/sprites/ground.json"});
    hitbox.insertAt(ground1Id, Component::HitBox {ground1Conf["hitbox"]["width"], ground1Conf["hitbox"]["height"]});

    size_t ground2Id = world.createEntity();
    vec.insertAt(ground2Id, ECS::Utils::Vector2f {ground2Conf["position"]["x"], ground2Conf["position"]["y"]});
    speed.insertAt(ground2Id, Component::Speed {ground2Conf["speed"]});
    type.insertAt(ground2Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground2Id, Component::LoadedSprite {"config/flappybird/sprites/ground.json"});
    hitbox.insertAt(ground2Id, Component::HitBox {ground2Conf["hitbox"]["width"], ground2Conf["hitbox"]["height"]});

    // Setup player entity
    size_t birdId = world.createEntity();
    vec.insertAt(birdId, ECS::Utils::Vector2f {birdConf["position"]["x"], birdConf["position"]["y"]});
    type.insertAt(birdId, Component::TypeEntity {EntityType::BIRD});
    sprite.insertAt(birdId, Component::LoadedSprite {"config/flappybird/sprites/bird.json"});
    weight.insertAt(birdId, Component::Weight(birdConf["weight"], physicConf._initialJumpVelocity));
    jump.insertAt(birdId, Component::Jump(birdConf["jump"]["strength"], birdConf["jump"]["height"],
                                          birdConf["jump"]["floating"]));
    hitbox.insertAt(birdId, Component::HitBox {birdConf["hitbox"]["width"], birdConf["hitbox"]["height"]});

    // Load systems
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem(ECS::System::moveGround);
    world.addSystem(ECS::System::killBird);
    world.addSystem(ECS::System::updateScore);

    // Game loop
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    while (world.isRunning()) {
        world.runSystems();
        eventManager->keepEventsAndClear<>();
        world.calcDeltaTime();
    }
    return SUCCESS;
}