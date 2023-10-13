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
        std::cout << "start client" << std::endl;
        RType::Packet connectPacket(static_cast<int>(RType::ServerEventType::CONNECT));
        std::cout << "made connect packet" << std::endl;
        client.send(connectPacket);
        std::cout << "sent connect packet" << std::endl;

        // Setup ECS / graphic
        std::cout << "start ECS" << std::endl;
        ECS::Core::World &world = ECS::Core::World::getInstance();
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        std::cout << "ECS started" << std::endl;

        // Components
        std::cout << "register components" << std::endl;
        world.registerComponent<ECS::Utils::Vector2f>();
        world.registerComponent<Component::Speed>();
        world.registerComponent<Component::TypeEntity>();
        world.registerComponent<Component::LoadedSprite>();
        world.registerComponent<Component::HitBox>();
        world.registerComponent<Component::IsAlive>();
        std::cout << "components registered" << std::endl;

        // Graphic systems
        std::cout << "add systems graphs" << std::endl;
        world.addSystem(ECS::System::getInput);
        world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
        world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
        world.addSystem(ECS::System::quitSDL);
        std::cout << "systems graphs added" << std::endl;

        // Background systems
        std::cout << "add systems background" << std::endl;
        world.addSystem(ECS::System::createBackground);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);
        std::cout << "systems background added" << std::endl;

        // Player systems
        std::cout << "add systems player" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::IsAlive>(
            ECS::System::movePlayer);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive>(
            ECS::System::triggerPlayerShoot);
        std::cout << "systems player added" << std::endl;

        // Bot systems
        std::cout << "add systems bot" << std::endl;
        world.addSystem(ECS::System::createBot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::updateBotPosition);
        world.addSystem(ECS::System::triggerBotShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::botHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite>(
            ECS::System::triggerBotDeath);
        world.addSystem<Component::TypeEntity>(ECS::System::triggerBotDisconnect);
        std::cout << "systems bot added" << std::endl;

        // Enemy systems
        std::cout << "add systems enemy" << std::endl;
        world.addSystem(ECS::System::createEnemy);
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
        world.addSystem(ECS::System::triggerEnemyShoot);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox>(ECS::System::enemyHit);
        world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite, ECS::Utils::Vector2f>(
            ECS::System::triggerEnemyDeath);
        std::cout << "systems enemy added" << std::endl;

        // Bonus systems
        std::cout << "add systems bonus" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBonus);
        world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
            ECS::System::triggerBonus);
        world.addSystem<Component::Speed, Component::TypeEntity>(ECS::System::triggerBotBonus);
        std::cout << "systems bonus added" << std::endl;

        // Missile systems
        std::cout << "add systems missile" << std::endl;
        world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);
        std::cout << "systems missile added" << std::endl;

        // Error message system
        std::cout << "add systems error" << std::endl;
        world.addSystem(ECS::System::createServerFullErrorMessage);
        std::cout << "systems error added" << std::endl;

        // Loading message
        std::cout << "add loading message" << std::endl;
        display.addEntity(
            ECS::Utils::Vector2f {SCREEN_WIDTH / 2 - LOADING_MESSAGE_TEX_WIDTH / 2,
                                  SCREEN_HEIGHT / 2 - LOADING_MESSAGE_TEX_HEIGHT / 2},
            Component::Speed {0}, Component::TypeEntity {false, false, false, false, false, false, false},
            Component::LoadedSprite {LOADING_MESSAGE_ASSET, nullptr, nullptr,
                                     new SDL_Rect {0, 0, LOADING_MESSAGE_TEX_WIDTH, LOADING_MESSAGE_TEX_HEIGHT}},
            Component::HitBox {}, Component::IsAlive {false, 0});
        std::cout << "loading message added" << std::endl;

        // Game loop
        while (world.isRunning()) {
            std::cout << "will run system loop" << std::endl;
            world.runSystems();
            std::cout << "did run system loop" << std::endl;
            std::cout << "will run render" << std::endl;
            SDL_RenderPresent(display._renderer);
            std::cout << "did run render" << std::endl;
            std::cout << "will clear event" << std::endl;
            eventManager->clearNonGameEvents();
            std::cout << "did clear event" << std::endl;
            std::cout << "will calc time" << std::endl;
            world.calcDeltaTime();
            std::cout << "did calc time" << std::endl;
        }

        // Quit server properly
        std::cout << "will make disconnect packet" << std::endl;
        RType::Packet disconnectPacket(static_cast<int>(RType::ServerEventType::DISCONNECT));
        std::cout << "will send disconnect packet" << std::endl;
        client.send(disconnectPacket);
        std::cout << "did send disconnect packet" << std::endl;
        Network::NetworkHandler::getInstance().stop();
        std::cout << "did stop network" << std::endl;
    } catch (std::exception &e) {
        Network::NetworkHandler::getInstance().stop();
        std::cerr << "[RType client exception] " << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
