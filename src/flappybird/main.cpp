#include <iostream>
#include "Components.hpp"
#include "ConfigReader.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "World.hpp"

int main(int ac, char **av)
{
    (void) ac;
    (void) av;

    // Load config
    ConfigReader &configReader = ConfigReader::getInstance();
    configReader.loadConfig();
    auto &graphicsConf = configReader.get()["graphics"];
    auto &physicsConf = configReader.get()["physics"];
    auto &backgroundConf = configReader.get()["entities"]["background"];
    auto &ground1Conf = configReader.get()["entities"]["ground_1"];
    auto &ground2Conf = configReader.get()["entities"]["ground_2"];
    auto &birdConf = configReader.get()["entities"]["bird"];

    // Load components
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &speed = world.registerComponent<Component::Speed>();
    auto &type = world.registerComponent<Component::TypeEntity>();
    auto &sprite = world.registerComponent<Component::LoadedSprite>();
    auto &weight = world.registerComponent<Component::Weight>();
    auto &jump = world.registerComponent<Component::Jump>();

    // Setup background
    size_t backgroundId = world.createEntity();
    vec.insertAt(backgroundId, ECS::Utils::Vector2f {0, 0});
    type.insertAt(backgroundId, Component::TypeEntity {EntityType::BACKGROUND});
    sprite.insertAt(
        backgroundId,
        Component::LoadedSprite {backgroundConf["sprite"], nullptr,
                                 new SDL_Rect {0, 0, backgroundConf["size"]["width"], backgroundConf["size"]["height"]},
                                 new SDL_Rect {0, 0, static_cast<int>(backgroundConf["size"]["width"]),
                                               static_cast<int>(backgroundConf["size"]["height"])}});

    // Setup ground entities
    size_t ground1Id = world.createEntity();
    vec.insertAt(ground1Id, ECS::Utils::Vector2f {0, ground1Conf["position"]["y"]});
    speed.insertAt(ground1Id, Component::Speed {ground1Conf["speed"]});
    type.insertAt(ground1Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground1Id, Component::LoadedSprite {
                                   ground1Conf["sprite"], nullptr,
                                   new SDL_Rect {0, 0, ground1Conf["size"]["width"], ground1Conf["size"]["height"]},
                                   new SDL_Rect {0, 0, static_cast<int>(ground1Conf["size"]["width"]),
                                                 static_cast<int>(ground1Conf["size"]["height"])}});

    size_t ground2Id = world.createEntity();
    vec.insertAt(ground2Id, ECS::Utils::Vector2f {ground2Conf["position"]["x"], ground2Conf["position"]["y"]});
    speed.insertAt(ground2Id, Component::Speed {ground2Conf["speed"]});
    type.insertAt(ground2Id, Component::TypeEntity {EntityType::GROUND});
    sprite.insertAt(ground2Id, Component::LoadedSprite {
                                   ground2Conf["sprite"], nullptr,
                                   new SDL_Rect {0, 0, ground2Conf["size"]["width"], ground2Conf["size"]["height"]},
                                   new SDL_Rect {0, 0, static_cast<int>(ground2Conf["size"]["width"]),
                                                 static_cast<int>(ground2Conf["size"]["height"])}});

    // Setup player entity
    size_t birdId = world.createEntity();
    vec.insertAt(birdId, ECS::Utils::Vector2f {birdConf["position"]["x"], birdConf["position"]["y"]});
    type.insertAt(birdId, Component::TypeEntity {EntityType::BIRD});
    sprite.insertAt(birdId,
                    Component::LoadedSprite {birdConf["sprite"], nullptr,
                                             new SDL_Rect {0, 0, birdConf["size"]["width"], birdConf["size"]["height"]},
                                             new SDL_Rect {0, 0, static_cast<int>(birdConf["size"]["width"]),
                                                           static_cast<int>(birdConf["size"]["height"])}});
    weight.insertAt(birdId, Component::Weight(birdConf["weight"], physicsConf["initial_fall_velocity"]));
    jump.insertAt(birdId, Component::Jump(birdConf["jump"]["strength"], birdConf["jump"]["height"],
                                          birdConf["jump"]["floating"]));

    // Load systems
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Weight>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveGround);
    world.addSystem(ECS::System::quitSDL);

    // Game loop
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearNonGameEvents();
        world.calcDeltaTime();
    }
    return SUCCESS;
}