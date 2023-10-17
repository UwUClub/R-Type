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
    auto &playerConf = configReader.getPlayer();

    // Load components
    ECS::Core::World &world = ECS::Core::World::getInstance();
    world.registerComponent<ECS::Utils::Vector2f>();
    world.registerComponent<Component::Speed>();
    world.registerComponent<Component::TypeEntity>();
    world.registerComponent<Component::LoadedSprite>();
    world.registerComponent<Component::Weight>();
    world.registerComponent<Component::Jump>();

    // Setup entities
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - (float) playerConf["width"] / 2, 10},
                      Component::Speed {playerConf["speed"]}, Component::Weight {playerConf["weight"]},
                      Component::TypeEntity {true, false},
                      Component::LoadedSprite {
                          playerConf["asset"], nullptr, new SDL_Rect {0, 0, playerConf["width"], playerConf["height"]},
                          new SDL_Rect {0, 0, (int) playerConf["width"] * 2, (int) playerConf["height"] * 2}},
                      Component::Jump {playerConf["jump"]["strength"], playerConf["jump"]["height"]});

    // Load systems
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Weight>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, Component::Jump, Component::Weight>(ECS::System::jump);
    world.addSystem(ECS::System::quitSDL);

    // Game loop
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearNonGameEvents();
        world.calcDeltaTime();
    }
    return SUCCESS;
}