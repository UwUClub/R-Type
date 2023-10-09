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
        return 84;
    }

    std::string host(av[1]);
    std::string port(av[2]);
    auto &client = Network::ClientHandler::getInstance();
    client.start(host, port);
    RType::Packet connectPacket(static_cast<int>(RType::ServerEventType::CONNECT));
    client.send(connectPacket);

    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
    world.registerComponent<ECS::Utils::Vector2f>();
    world.registerComponent<Component::Speed>();
    world.registerComponent<Component::TypeEntity>();
    world.registerComponent<Component::LoadedSprite>();
    world.registerComponent<Component::HitBox>();
    world.registerComponent<Component::IsAlive>();
    world.addSystem(ECS::System::getInput);
    world.addSystem<Component::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem(ECS::System::createBot);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity, Component::IsAlive>(
        ECS::System::movePlayer);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity>(ECS::System::updateBotPosition);
    world.addSystem(ECS::System::triggerBotShoot);
    world.addSystem(ECS::System::quitSDL);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBackground);
    world.addSystem(ECS::System::createEnemy);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveEnemy);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive>(ECS::System::triggerPlayerShoot);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveMissiles);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::HitBox, Component::IsAlive>(
        ECS::System::destroyEnemy);
    world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::handleEnemyDeath);
    world.addSystem(ECS::System::triggerEnemyShoot);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(
        ECS::System::killPlayer);
    world.addSystem<Component::TypeEntity, Component::IsAlive, Component::LoadedSprite>(ECS::System::handlePlayerDeath);
    world.addSystem<ECS::Utils::Vector2f, Component::Speed, Component::TypeEntity>(ECS::System::moveBonus);
    world.addSystem<ECS::Utils::Vector2f, Component::TypeEntity, Component::IsAlive, Component::HitBox>(ECS::System::triggerBonus);
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

    while (world.isRunning()) {
        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearNonGameEvents();
        world.calcDeltaTime();
    }
    Network::NetworkHandler::getInstance().stop();
    return 0;
}
