#include <boost/asio.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "Jump.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "Weight.hpp"
#include "World.hpp"

int main(int ac, char **av)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    SDLDisplayClass &display = SDLDisplayClass::getInstance();
    ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();

    auto &vec = world.registerComponent<ECS::Utils::Vector2f>();
    auto &spd = world.registerComponent<ECS::Utils::Speed>();
    auto &type = world.registerComponent<ECS::Utils::TypeEntity>();
    auto &sprite = world.registerComponent<ECS::Utils::LoadedSprite>();

    auto &weight = world.registerComponent<ECS::Utils::Weight>();
    auto &jump = world.registerComponent<ECS::Utils::Jump>();

    size_t idPlayer = world.createEntity();

    vec.insertAt(idPlayer, ECS::Utils::Vector2f {325, 10});
    spd.insertAt(idPlayer, ECS::Utils::Speed {10});
    weight.insertAt(idPlayer, ECS::Utils::Weight {170});
    type.insertAt(idPlayer, ECS::Utils::TypeEntity {true, false, false, false, false});
    sprite.insertAt(idPlayer, ECS::Utils::LoadedSprite {"assets/sprites/bluebird-upflap.png",
                                                        nullptr,
                                                        {0, 0, 34, 24},
                                                        {0, 0, 34 * 2, 24 * 2}});
    jump.insertAt(idPlayer, ECS::Utils::Jump {7, 100});

    world.addSystem(ECS::System::getInput);
    world.addSystem<ECS::Utils::LoadedSprite>(ECS::System::loadTextures);
    world.addSystem<ECS::Utils::LoadedSprite, ECS::Utils::Vector2f>(ECS::System::displayEntities);
    world.addSystem<ECS::Utils::Vector2f, ECS::Utils::Weight, ECS::Utils::TypeEntity>(ECS::System::applyGravity);
    world.addSystem<ECS::Utils::Vector2f, ECS::Utils::Jump, ECS::Utils::TypeEntity>(ECS::System::jump);
    world.addSystem(ECS::System::quitSDL);

    auto time = std::chrono::system_clock::now();

    while (1) {
        auto delta = std::chrono::system_clock::now() - time;
        float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(delta).count();
        world.setDeltaTime(deltaTime);
        time += delta;

        world.runSystems();
        SDL_RenderPresent(display._renderer);
        eventManager->clearEvents();
        // std::cout << vec[idPlayer].value().x << std::endl;
        // std::cout << vec[idPlayer].value().y << std::endl;
    }
    return 0;
}