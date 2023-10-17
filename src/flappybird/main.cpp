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
    auto &playerConf = configReader.get()["player"];
    auto &physicsConf = configReader.get()["physics"];
    auto &backgroundConf = configReader.get()["background"];
    auto &graphicsConf = configReader.get()["graphics"];

    // Load components
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &speed = world.registerComponent<Component::Speed>();
    auto &type = world.registerComponent<Component::TypeEntity>();
    auto &sprite = world.registerComponent<Component::LoadedSprite>();
    auto &weight = world.registerComponent<Component::Weight>();
    auto &jump = world.registerComponent<Component::Jump>();

    // Setup 1st background entity
    size_t backgroundId1 = world.createEntity();
    vec.insertAt(backgroundId1, ECS::Utils::Vector2f {0, 0});
    speed.insertAt(backgroundId1, Component::Speed {backgroundConf["speed"]});
    type.insertAt(backgroundId1, Component::TypeEntity {false, true});
    sprite.insertAt(backgroundId1,
                    Component::LoadedSprite {backgroundConf["sprite"], nullptr,
                                             new SDL_Rect {0, 0, backgroundConf["width"], backgroundConf["height"]},
                                             new SDL_Rect {0, 0, static_cast<int>(backgroundConf["width"]),
                                                           static_cast<int>(backgroundConf["height"])}});

    // Setup 2nd background entity
    size_t backgroundId2 = world.createEntity();
    vec.insertAt(backgroundId2, ECS::Utils::Vector2f {graphicsConf["width"], 0});
    speed.insertAt(backgroundId2, Component::Speed {backgroundConf["speed"]});
    type.insertAt(backgroundId2, Component::TypeEntity {false, true});
    sprite.insertAt(backgroundId2,
                    Component::LoadedSprite {backgroundConf["sprite"], nullptr,
                                             new SDL_Rect {0, 0, backgroundConf["width"], backgroundConf["height"]},
                                             new SDL_Rect {0, 0, static_cast<int>(backgroundConf["width"]),
                                                           static_cast<int>(backgroundConf["height"])}});

    // Setup player entity
    size_t playerId = world.createEntity();
    vec.insertAt(playerId,
                 ECS::Utils::Vector2f {
                     static_cast<float>(graphicsConf["width"]) / 2 - static_cast<float>(playerConf["width"]) / 2, 10});
    type.insertAt(playerId, Component::TypeEntity {true, false});
    sprite.insertAt(playerId, Component::LoadedSprite {playerConf["sprite"], nullptr,
                                                       new SDL_Rect {0, 0, playerConf["width"], playerConf["height"]},
                                                       new SDL_Rect {0, 0, static_cast<int>(playerConf["width"]),
                                                                     static_cast<int>(playerConf["height"])}});
    weight.insertAt(playerId, Component::Weight(playerConf["weight"], physicsConf["initial_fall_velocity"]));
    jump.insertAt(playerId, Component::Jump(playerConf["jump"]["strength"], playerConf["jump"]["height"],
                                            playerConf["jump"]["floating"]));

    // Load systems
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Weight>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);
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