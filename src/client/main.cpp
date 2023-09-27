#include <boost/asio.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "World.hpp"
#include "ClientNetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"

int main(int ac, char **av)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &spd = world.registerComponent<ECS::Utils::Speed>();
    auto &type = world.registerComponent<ECS::Utils::TypeEntity>();
    auto &sprite = world.registerComponent<ECS::Utils::LoadedSprite>();

    size_t idPlayer = world.createEntity();

    vec.insertAt(idPlayer, ECS::Utils::Vector2f {10, 10});
    spd.insertAt(idPlayer, ECS::Utils::Speed {10});
    type.insertAt(idPlayer, ECS::Utils::TypeEntity {true, false, false, false, false});
    sprite.insertAt(
        idPlayer,
        ECS::Utils::LoadedSprite {"assets/sprites/r-typesheet42.png", nullptr, {0, 0, 33, 17}, {300, 15, 33, 17}});
    world.addSystem(ECS::System::getInput);
    world.addSystem<ECS::Utils::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<ECS::Utils::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, ECS::Utils::Speed, ECS::Utils::TypeEntity>(ECS::System::movePlayer);
    world.addSystem(ECS::System::quitSDL);
    while (1) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearEvents();
        std::cout << vec[idPlayer].value().x << std::endl;
        std::cout << vec[idPlayer].value().y << std::endl;
    }
    return 0;
}