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
#include "World.hpp"
#include <SDL_rect.h>

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
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

        // Components
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::LoadedSprite>();
        world.registerComponent<Component::HitBox>();
        world.registerComponent<Component::IsAlive>();

        // Graphic systems
        world.addSystem(ECS::System::getInput);
        world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
        world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
        world.addSystem(ECS::System::quitSDL);

        // Bot systems
        world.addSystem(ECS::System::createBot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::updateBotPosition);
        world.addSystem(ECS::System::triggerBotShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::botHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite>(
            ECS::System::triggerBotDeath);
        world.addSystem<Component::TypeEntity>(ECS::System::triggerBotDisconnect);

        // Player systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::IsAlive>(
            ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive>(
            ECS::System::triggerPlayerShoot);

        // Enemy systems
        world.addSystem(ECS::System::createEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem(ECS::System::triggerEnemyShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox>(ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite>(
            ECS::System::triggerEnemyDeath);

        // Missile systems
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);

        // Setup background
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);
        display.addEntity(ECS::Utils::Vector2f {0, 0}, Component::Speed {BACKGROUND_SPEED},
                          Component::TypeEntity {false, false, false, false, false, false, true},
                          Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                   new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                          Component::HitBox {}, Component::IsAlive {false, 0});
        display.addEntity(ECS::Utils::Vector2f {SCREEN_WIDTH, 0}, Component::Speed {BACKGROUND_SPEED},
                          Component::TypeEntity {false, false, false, false, false, false, true},
                          Component::LoadedSprite {BACKGROUND_ASSET, nullptr, nullptr,
                                                   new SDL_Rect {400, 15, SCREEN_WIDTH, SCREEN_HEIGHT}},
                          Component::HitBox {}, Component::IsAlive {false, 0});

        // Game loop
        while (world.isRunning()) {
            world.runSystems();
            SDL_RenderPresent(display._renderer);
            eventManager->clearNonGameEvents();
            world.calcDeltaTime();
        }

        // Quit server properly
        RType::Packet disconnectPacket(static_cast<int>(RType::ServerEventType::DISCONNECT));
        client.send(disconnectPacket);
        Network::NetworkHandler::getInstance().stop();
    } catch (std::exception &e) {
        std::cerr << "[RType client exception] " << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
