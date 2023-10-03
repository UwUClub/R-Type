#include <iostream>
#include "Components.hpp"
#include "EventManager.hpp"
#include "ServerNetworkHandler.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "World.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        return 84;
    }

    try {
        std::string host(av[1]);
        unsigned short port = static_cast<unsigned short>(std::stoi(av[2]));
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();
        network.start(host, port);

        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

        auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
        auto &spd = world.registerComponent<Component::Speed>();
        auto &type = world.registerComponent<Component::TypeEntity>();

        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::welcomePlayers);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::movePlayer);

        while (world.isRunning()) {
            world.runSystems();
            eventManager->clearNonGameEvents();
        }

        network.stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
