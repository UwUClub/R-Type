#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "SDLDisplayClass.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "World.hpp"

void runNetwork(std::string aHost, std::string aPort)
{
    try {
        Network::ClientNetworkHandler &network = Network::ClientNetworkHandler::getInstance(aHost, aPort);

        RTypeProtocol::ClientToServerPacket packet;
        packet.type = RTypeProtocol::ServerEventType::MOVE_UP;
        network.send(packet);

        std::string exitWord;
        std::cin >> exitWord;

        network.stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        return 84;
    }

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
    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearEvents();
        std::cout << vec[idPlayer].value().x << std::endl;
        std::cout << vec[idPlayer].value().y << std::endl;
    }

    std::string host(av[1]);
    std::string port(av[2]);
    runNetwork(host, port);
    return 0;
}