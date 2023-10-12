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
        std::cerr << "Usage: ./server <host> <port>" << std::endl;
        return FAILURE;
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
        world.registerComponent<Component::Connection>();

        //-----Events subscription
        // Player systems subscription
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::welcomePlayer);
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::movePlayer);
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::playerShoot);
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::disconnectPlayer);
        // Bonus systems subscription
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::moveSpeedUp);
        // Network systems subscription
        eventManager->subscribe<RType::ServerGameEvent>(ECS::System::receiveAknowledgment);

        // Player systems
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::playerHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection>(ECS::System::killPlayer);

        // Network systems
        world.addSystem<Component::IsAlive, Component::TypeEntity, Component::Connection>(
            ECS::System::handlePlayerCrash);

        // Enemy systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::spawnEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::enemyShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox, Component::IsAlive>(
            ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection>(ECS::System::killEnemy);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            world.calcDeltaTime();
        }

        Network::NetworkHandler::getInstance().stop();
    } catch (std::exception &e) {
        Network::NetworkHandler::getInstance().stop();
        std::cout << "[RType server exception] " << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
