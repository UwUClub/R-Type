#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
#include "Components.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "SDLDisplayClass.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "World.hpp"
#include <SDL_rect.h>

int main(int ac, char **av)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    world.registerComponent<ECS::Utils::Vector2f>();
    world.registerComponent<Component::Speed>();
    world.registerComponent<Component::TypeEntity>();
    world.registerComponent<Component::LoadedSprite>();
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::movePlayer);
    world.addSystem(ECS::System::quitSDL);

    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {0},
                      Component::TypeEntity {false, false, false, false, false, true},
                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr, NULL, NULL});
    // display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {0},
    //                   Component::TypeEntity {false, false, false, false, false, true},
    //                   Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr, nullptr});
    display.addEntity(
        ECS::Utils::Vector2f {10, 10}, Component::Speed {10},
        Component::TypeEntity {true, false, false, false, false, false},
        Component::LoadedSprite {PLAYER_ASSET, nullptr, new SDL_Rect {0, 0, 33, 17}, new SDL_Rect {300, 15, 33, 17}});

    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearEvents();
    }
    return 0;
}
