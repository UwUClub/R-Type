#include <iostream>
#include "Components.hpp"
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
    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

    world.registerComponent<ECS::Utils::Vector2f>();
    world.registerComponent<Component::Speed>();
    world.registerComponent<Component::TypeEntity>();
    world.registerComponent<Component::LoadedSprite>();
    world.registerComponent<Component::Weight>();
    world.registerComponent<Component::Jump>();

    display.addEntity(
        ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - PLAYER_TEX_WIDTH / 2, 10}, Component::Speed {PLAYER_SPEED},
        Component::Weight {PLAYER_WEIGHT}, Component::TypeEntity {true, false},
        Component::LoadedSprite {PLAYER_ASSET, nullptr, new SDL_Rect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                 new SDL_Rect {0, 0, PLAYER_TEX_WIDTH * 2, PLAYER_TEX_HEIGHT * 2}},
        Component::Jump {PLAYER_JUMP_STRENGTH, PLAYER_JUMP_HEIGHT});

    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Weight>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, Component::Jump>(ECS::System::jump);
    world.addSystem(ECS::System::quitSDL);

    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearNonGameEvents();
        world.calcDeltaTime();
    }
    return SUCCESS;
}