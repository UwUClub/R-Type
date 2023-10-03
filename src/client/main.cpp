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
    world.registerComponent<ECS::Utils::Vector2f>();
    world.registerComponent<Component::Speed>();
    world.registerComponent<Component::TypeEntity>();
    world.registerComponent<Component::LoadedSprite>();
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::movePlayer);
    world.addSystem(ECS::System::quitSDL);

    std::string host(av[1]);
    std::string port(av[2]);
    Network::ClientNetworkHandler &network = Network::ClientNetworkHandler::getInstance();
    network.start(host, port);
    network.send({RTypeProtocol::ServerEventType::CONNECT});

    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {0},
                      Component::TypeEntity {false, false, false, false, false, true},
                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr, {0, 0, 800, 600}, {0, 0, 800, 600}});
    display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {0},
                      Component::TypeEntity {false, false, false, false, false, true},
                      Component::LoadedSprite {BACKGROUND_ASSET, nullptr, {0, 0, 800, 600}, {800, 0, 800, 600}});
    display.addEntity(ECS::Utils::Vector2f {10, 10}, Component::Speed {10},
                      Component::TypeEntity {true, false, false, false, false, false},
                      Component::LoadedSprite {PLAYER_ASSET, nullptr, {0, 0, 33, 17}, {300, 15, 33, 17}});

    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearEvents();
    }
    network.stop();
    return 0;
}
