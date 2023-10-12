#include <boost/asio.hpp>
#include <iostream>
#include "ClientHandler.hpp"
#include "Components.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "IsAlive.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "SDLDisplayClass.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "TypeEntity.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"
#include <SDL_rect.h>

int main(int argc, const char **argv)
{
    if (argc < 3) {
        std::cerr << "Usage: ./client <host> <port>" << std::endl;
        return FAILURE;
    }

    try {
        // Network
        std::string host(argv[1]);
        std::string port(argv[2]);
        auto &client = Network::ClientHandler::getInstance();

        // Setup ECS / graphic
        ECS::Core::World &world = ECS::Core::World::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

        //-------Components
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::LoadedSprite>();
        world.registerComponent<Component::HitBox>();
        world.registerComponent<Component::IsAlive>();

        //-------Events subscription
        eventManager->subscribe<ECS::Event::WindowEvent>(ECS::System::quitSDL);
        // Player systems subscription
        eventManager->subscribe<ECS::Event::KeyboardEvent>(ECS::System::movePlayer);
        eventManager->subscribe<ECS::Event::KeyboardEvent>(ECS::System::triggerPlayerShoot);
        // Bot systems subscription
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::createBot);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::updateBotPosition);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerBotShoot);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerBotDeath);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerBotDisconnect);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerBotBonus);
        // Enemy systems subscription
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::createEnemy);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerEnemyShoot);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::triggerEnemyDeath);
        // Error message subscription
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::createServerFullErrorMessage);
        eventManager->subscribe<RType::ClientGameEvent>(ECS::System::createBackground);

        // Graphic systems
        world.addSystem(ECS::System::getInput);
        world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
        world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);

        // Background systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);

        // Bot systems
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox>(ECS::System::botHit);

        // Enemy systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox>(ECS::System::enemyHit);

        // Bonus systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBonus);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::triggerBonus);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Loading message
        // display.addEntity(
        //     ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - LOADING_MESSAGE_TEX_WIDTH / 2,
        //                           SCREEN_HEIGHT / 2 - LOADING_MESSAGE_TEX_HEIGHT / 2},
        //     Component::Speed {0}, Component::TypeEntity {false, false, false, false, false, false, false},
        //     Component::LoadedSprite {LOADING_MESSAGE_ASSET, nullptr, nullptr,
        //                              new SDL_Rect {0, 0, LOADING_MESSAGE_TEX_WIDTH, LOADING_MESSAGE_TEX_HEIGHT}},
        //     Component::HitBox {}, Component::IsAlive {false, 0});

        client.start(host, port);
        RType::Packet connectPacket(static_cast<int>(RType::ServerEventType::CONNECT));
        client.send(connectPacket);
        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            SDL_RenderPresent(display._renderer);
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
