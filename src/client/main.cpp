#include "AddEntity.hpp"
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Music/MusicPlugin.hpp"
#include "EwECS/Network/ClientHandler.hpp"
#include "EwECS/Network/Packet.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Sound/SoundPlugin.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "PacketFactory.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "TypeEntity.hpp"
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
        std::string port(av[2]);
        auto &client = ECS::Network::ClientHandler::getInstance();

        client.onReceive([](int8_t aPacketType, ECS::Network::IPayload *aPayload) {
            if (aPacketType >= RType::ClientEventType::MAX_CLI_EVT) {
                return;
            }
            if (aPacketType >= 0) {
                auto eventType = static_cast<RType::ClientEventType>(aPacketType);

                ECS::Event::EventManager::getInstance()->pushEvent<RType::ClientGameEvent>(
                    RType::ClientGameEvent(eventType, aPayload));
            }
        });

        client.start(host, port, RType::packetFactory);
        client.send(RType::ServerEventType::CONNECT);

        // Setup ECS / graphic
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Render::RenderPlugin renderPlugin;
        ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
        ECS::Physic::PhysicPlugin physicPlugin;
        ECS::SoundPlugin soundPlugin;
        ECS::MusicPlugin musicPlugin;

        // Graphic systems plug

        // Components
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::IsAlive>();

        ECS::Physic::PhysicPluginConfig::getInstance().load("config/r-type.json");
        ECS::Render::RenderPluginConfig::getInstance().load("config/r-type.json");
        physicPlugin.plug(world, assetManager);
        renderPlugin.plug(world, assetManager);
        soundPlugin.plug(world, assetManager);
        musicPlugin.plug(world, assetManager);

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
        world.addSystem<Component::Speed, Component::TypeEntity>(ECS::System::triggerBonus);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Error message system
        world.addSystem(ECS::System::createServerFullErrorMessage);

        // Loading message
        try {
            AddEntity::addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - LOADING_MESSAGE_TEX_WIDTH / 2,
                                                       SCREEN_HEIGHT / 2 - LOADING_MESSAGE_TEX_HEIGHT / 2},
                                 Component::Speed {0},
                                 Component::TypeEntity {false, false, false, false, false, false, false},
                                 Component::LoadedSprite {"config/serverMessage.json"}, Component::HitBox {},
                                 Component::IsAlive {false, 0});
        } catch (std::exception &e) {
            ECS::Logger::error("[RType client exception] " + std::string(e.what()));
            ECS::Network::ClientHandler::getInstance().stop();
            return FAILURE;
        }

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            eventManager->keepEventsAndClear<RType::ClientGameEvent>();
            world.calcDeltaTime();
        }

        // Quit server properly
        client.send(RType::ServerEventType::DISCONNECT);
        ECS::Network::ClientHandler::getInstance().stop();
    } catch (std::exception &e) {
        ECS::Network::ClientHandler::getInstance().stop();
        ECS::Logger::error("[RType client exception] " + std::string(e.what()));
        return FAILURE;
    }
    return SUCCESS;
}
