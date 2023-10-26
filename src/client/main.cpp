#include <boost/asio.hpp>
#include <iostream>
#include "AddEntity.hpp"
#include "ClientHandler.hpp"
#include "Components.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "TypeEntity.hpp"
#include "Values.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        return FAILURE;
    }

    try {
        // Network
        std::string host(av[1]);
        std::string port(av[2]);
        auto &client = Network::ClientHandler::getInstance();
        client.start(host, port);
        RType::Packet connectPacket(static_cast<int>(RType::ServerEventType::CONNECT));
        client.send(connectPacket);

        // Setup ECS / graphic
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Render::RenderPlugin renderPlugin;
        ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
        ECS::Physic::PhysicPlugin physicPlugin;

        // Graphic systems plug

        // Components
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::IsAlive>();

        ECS::Physic::PhysicPluginConfig::getInstance().load("config/r-type.json");
        ECS::Render::RenderPluginConfig::getInstance().load("config/r-type.json");
        physicPlugin.plug(world, assetManager);
        renderPlugin.plug(world, assetManager);

        // Background systems
        world.addSystem(ECS::System::createBackground);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);

        // Player systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::IsAlive>(
            ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive>(
            ECS::System::triggerPlayerShoot);

        // Bot systems
        world.addSystem(ECS::System::createBot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::updateBotPosition);
        world.addSystem(ECS::System::triggerBotShoot);
        world.addSystem<Component::TypeEntity, Component::HitBox>(ECS::System::botHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite>(
            ECS::System::triggerBotDeath);
        world.addSystem<Component::TypeEntity>(ECS::System::triggerBotDisconnect);

        // Enemy systems
        world.addSystem(ECS::System::createEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem(ECS::System::triggerEnemyShoot);
        world.addSystem<Component::TypeEntity, Component::HitBox>(ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite, ECS::Utils::Vector2f>(
            ECS::System::triggerEnemyDeath);

        // Bonus systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBonus);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::triggerBonus);
        world.addSystem<Component::Speed, Component::TypeEntity>(ECS::System::triggerBotBonus);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Error message system
        world.addSystem(ECS::System::createServerFullErrorMessage);

        // Loading message
        AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - LOADING_MESSAGE_TEX_WIDTH / 2,
                                                   SCREEN_HEIGHT / 2 - LOADING_MESSAGE_TEX_HEIGHT / 2},
                             Component::Speed {0},
                             Component::TypeEntity {false, false, false, false, false, false, false},
                             Component::LoadedSprite {LOADING_MESSAGE_ASSET, nullptr, 0, 0, LOADING_MESSAGE_TEX_WIDTH,
                                                      LOADING_MESSAGE_TEX_HEIGHT},
                             Component::HitBox {}, Component::IsAlive {false, 0});

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            eventManager->keepEventsAndClear<RType::ClientGameEvent>();
            world.calcDeltaTime();
        }

        // Quit server properly
        RType::Packet disconnectPacket(static_cast<int>(RType::ServerEventType::DISCONNECT));
        client.send(disconnectPacket);
        Network::NetworkHandler::getInstance().stop();
    } catch (std::exception &e) {
        Network::NetworkHandler::getInstance().stop();
        std::cerr << "[RType client exception] " << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
