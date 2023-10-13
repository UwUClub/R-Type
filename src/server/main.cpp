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
        return FAILURE;
    }

    try {
        // Network
        std::string host(av[1]);
        unsigned short port = static_cast<unsigned short>(std::stoi(av[2]));
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        std::cout << "will start server" << std::endl;
        server.start(host, port);
        std::cout << "server started" << std::endl;

        // Setup ECS
        std::cout << "start ECS" << std::endl;
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        std::cout << "ECS started" << std::endl;

        // Components
        std::cout << "register components" << std::endl;
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::HitBox>();
        world.registerComponent<Component::IsAlive>();
        world.registerComponent<Component::Connection>();
        std::cout << "components registered" << std::endl;

        // Player systems
        std::cout << "add systems player" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::welcomePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::Connection>(ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::Connection>(ECS::System::playerShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::playerHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection>(ECS::System::killPlayer);
        world.addSystem<Component::Speed, Component::Connection>(ECS::System::moveSpeedUp);
        world.addSystem<Component::Connection>(ECS::System::disconnectPlayer);
        std::cout << "systems player added" << std::endl;

        // Network systems
        std::cout << "add systems network" << std::endl;
        world.addSystem<Component::Connection>(ECS::System::receiveAknowledgment);
        world.addSystem<Component::IsAlive, Component::TypeEntity, Component::Connection>(
            ECS::System::handlePlayerCrash);
        std::cout << "systems network added" << std::endl;

        // Enemy systems
        std::cout << "add systems enemy" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::spawnEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::enemyShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox, Component::IsAlive>(
            ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection>(ECS::System::killEnemy);
        std::cout << "systems enemy added" << std::endl;

        // Missile systems
        std::cout << "add systems missile" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);
        std::cout << "systems missile added" << std::endl;

        // Game loop
        while (world.isRunning()) {
            std::cout << "will run systems" << std::endl;
            world.runSystems();
            std::cout << "systems runned" << std::endl;
            std::cout << "will clear non game events" << std::endl;
            eventManager->clearNonGameEvents();
            std::cout << "non game events cleared" << std::endl;
            std::cout << "will calc delta time" << std::endl;
            world.calcDeltaTime();
            std::cout << "delta time calculated" << std::endl;
        }

        Network::NetworkHandler::getInstance().stop();
    } catch (std::exception &e) {
        Network::NetworkHandler::getInstance().stop();
        std::cout << "[RType server exception] " << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
