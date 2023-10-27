#include <iostream>
#include "Components.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "PacketFactory.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "Values.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        ECS::Logger::error("Usage: " + std::string(av[0]) + " <host> <port>");
        return FAILURE;
    }

    try {
        // Network
        std::string host(av[1]);
        unsigned short port = static_cast<unsigned short>(std::stoi(av[2]));
        ECS::Network::ServerHandler &server = ECS::Network::ServerHandler::getInstance();
        server.onReceive([](int8_t aPacketType, ECS::Network::IPayload *aPayload, unsigned short entityId) {
            auto eventType = static_cast<RType::ServerEventType>(aPacketType);

            ECS::Event::EventManager::getInstance()->pushEvent<RType::ServerGameEvent>(
                RType::ServerGameEvent(eventType, entityId, aPayload));
        });
        server.onReceiveAknowledgment([](unsigned short aEntityId) {
            ECS::Event::EventManager::getInstance()->pushEvent<RType::ServerGameEvent>(
                RType::ServerGameEvent(RType::ServerEventType::AKNOWLEDGMENT, aEntityId, {}));
        });
        server.start(host, port, 4, RType::packetFactory);

        // Setup ECS
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();

        // Components
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::IsAlive>();
        world.registerComponent<Component::Connection>();

        ECS::Physic::PhysicPlugin physicPlugin;

        physicPlugin.plug(world, assetManager);

        // Player systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::welcomePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::Connection>(ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::Connection>(ECS::System::playerShoot);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::HitBox>(ECS::System::playerHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection>(ECS::System::killPlayer);
        world.addSystem<Component::Connection>(ECS::System::disconnectPlayer);

        // Bonus systems
        world.addSystem<Component::Speed, ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::moveBonus);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::HitBox, Component::Connection,
                        Component::Speed>(ECS::System::triggerBonus);

        // Network systems
        world.addSystem<Component::Connection>(ECS::System::receiveAknowledgment);
        world.addSystem<Component::IsAlive, Component::TypeEntity, Component::Connection>(
            ECS::System::handlePlayerCrash);

        // Enemy systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::spawnEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::HitBox,
                        Component::IsAlive, Component::Connection>(ECS::System::enemyShoot);
        world.addSystem<Component::TypeEntity, Component::HitBox, Component::IsAlive>(ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::Connection, ECS::Utils::Vector2f,
                        Component::HitBox, Component::Speed>(ECS::System::killEnemy);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            eventManager->keepEventsAndClear<RType::ServerGameEvent>();
            world.calcDeltaTime();
        }

        ECS::Network::ServerHandler::getInstance().stop();
    } catch (std::exception &e) {
        ECS::Network::ServerHandler::getInstance().stop();
        ECS::Logger::error("[RType server exception] " + std::string(e.what()));
        return FAILURE;
    }
    return SUCCESS;
}
