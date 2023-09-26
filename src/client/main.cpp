#include <iostream>
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "World.hpp"


int main()
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &spd = world.registerComponent<ECS::Utils::Speed>();
    auto &type = world.registerComponent<ECS::Utils::TypeEntity>();

    size_t idPlayer = world.createEntity();

    vec.insertAt(idPlayer, ECS::Utils::Vector2f {10, 10});
    spd.insertAt(idPlayer, ECS::Utils::Speed {10});
    type.insertAt(idPlayer, ECS::Utils::TypeEntity {true, false, false, false, false});
    world.addSystem(ECS::System::getInput);
    world.addSystem<ECS::Utils::Vector2f, ECS::Utils::Speed, ECS::Utils::TypeEntity>(ECS::System::movePlayer);
    world.addSystem(ECS::System::quitSDL);
    SDL_SetRenderDrawColor(display._renderer, 0, 0, 0, 255);
    SDL_RenderClear(display._renderer);
    while (1) {
        SDL_RenderPresent(display._renderer);
        world.runSystems();
        eventManager->clearEvents();
        std::cout << vec[idPlayer].value().x << std::endl;
        std::cout << vec[idPlayer].value().y << std::endl;
    }
    return 0;
}