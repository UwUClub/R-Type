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
    auto &birdConf = configReader.get()["entities"]["bird"];
    auto &backgroundConf = configReader.get()["entities"]["background"];
    auto &baseConf = configReader.get()["entities"]["base"];

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
    sprite.insertAt(backgroundId,
                    Component::LoadedSprite {backgroundConf["sprite"], nullptr,
                                             new SDL_Rect {0, 0, backgroundConf["width"], backgroundConf["height"]},
                                             new SDL_Rect {0, 0, static_cast<int>(backgroundConf["width"]),
                                                           static_cast<int>(backgroundConf["height"])}});

    // Setup base entities
    float basePosY = static_cast<float>(graphicsConf["height"]) - static_cast<float>(baseConf["height"]);
    size_t base1Id = world.createEntity();
    vec.insertAt(base1Id, ECS::Utils::Vector2f {0, basePosY});
    speed.insertAt(base1Id, Component::Speed {baseConf["speed"]});
    type.insertAt(base1Id, Component::TypeEntity {EntityType::BASE});
    sprite.insertAt(base1Id, Component::LoadedSprite {baseConf["sprite"], nullptr,
                                                      new SDL_Rect {0, 0, baseConf["width"], baseConf["height"]},
                                                      new SDL_Rect {0, 0, static_cast<int>(baseConf["width"]),
                                                                    static_cast<int>(baseConf["height"])}});

    size_t base2Id = world.createEntity();
    vec.insertAt(base2Id, ECS::Utils::Vector2f {graphicsConf["width"], basePosY});
    speed.insertAt(base2Id, Component::Speed {baseConf["speed"]});
    type.insertAt(base2Id, Component::TypeEntity {EntityType::BASE});
    sprite.insertAt(base2Id, Component::LoadedSprite {baseConf["sprite"], nullptr,
                                                      new SDL_Rect {0, 0, baseConf["width"], baseConf["height"]},
                                                      new SDL_Rect {0, 0, static_cast<int>(baseConf["width"]),
                                                                    static_cast<int>(baseConf["height"])}});

    // Setup player entity
    size_t birdId = world.createEntity();
    vec.insertAt(birdId,
                 ECS::Utils::Vector2f {
                     static_cast<float>(graphicsConf["width"]) / 2 - static_cast<float>(birdConf["width"]) / 2, 10});
    type.insertAt(birdId, Component::TypeEntity {EntityType::BIRD});
    sprite.insertAt(birdId, Component::LoadedSprite {birdConf["sprite"], nullptr,
                                                     new SDL_Rect {0, 0, birdConf["width"], birdConf["height"]},
                                                     new SDL_Rect {0, 0, static_cast<int>(birdConf["width"]),
                                                                   static_cast<int>(birdConf["height"])}});
    weight.insertAt(birdId, Component::Weight(birdConf["weight"], physicsConf["initial_fall_velocity"]));
    jump.insertAt(birdId, Component::Jump(birdConf["jump"]["strength"], birdConf["jump"]["height"],
                                          birdConf["jump"]["floating"]));

    // Load systems
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Weight>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBase);
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