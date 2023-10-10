#include <iostream>
#include "Components.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "NetworkHandler.hpp"
#include "ServerHandler.hpp"
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
        // Network
        std::string host(av[1]);
        unsigned short port = static_cast<unsigned short>(std::stoi(av[2]));
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        server.start(host, port);

        // Setup ECS
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

        // Components
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::HitBox>();
        world.registerComponent<Component::IsAlive>();

        // Player systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::welcomePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed>(ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox>(
            ECS::System::playerShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::playerHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive>(ECS::System::killPlayer);
        world.addSystem<Component::Speed>(ECS::System::moveSpeedUp);

        // Enemy systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive>(ECS::System::spawnEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive>(ECS::System::enemyShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox, Component::IsAlive>(
            ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive>(ECS::System::killEnemy);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            eventManager->clearNonGameEvents();
            world.calcDeltaTime();
        }

        Network::NetworkHandler::getInstance().stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
