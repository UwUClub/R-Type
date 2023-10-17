#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "Timer+SpawnEnemy.hpp"

namespace ECS {
    void System::spawnEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::HitBox> &aHitBox,
                            Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        Timer::TimerSpawnWall &timer = Timer::TimerSpawnWall::getInstance();
        auto &world = Core::World::getInstance();

        // Handle timer
        timer.add(world.getDeltaTime());
        if (timer.get() < WALL_SPAWN_INTERVAL) {
            return;
        }
        timer.reset();

        // Create entity
        for (size_t i = 0; i < SCREEN_HEIGHT; i += WALL_TEX_HEIGHT) {
            size_t wallId = world.createEntity();
            auto posX = static_cast<float>(SCREEN_WIDTH - WALL_TEX_WIDTH);
            auto posY = static_cast<float>(i);
            aPos.insertAt(wallId, ECS::Utils::Vector2f {posX, posY});
            aSpeed.insertAt(wallId, Component::Speed {WALL_SPEED});
            aType.insertAt(wallId, Component::TypeEntity {false, false, true, false, false, false, false});
            aHitBox.insertAt(
                wallId, Component::HitBox {static_cast<float>(ENEMY_TEX_WIDTH), static_cast<float>(ENEMY_TEX_HEIGHT)});
            aIsAlive.insertAt(wallId, Component::IsAlive {true, 0});

            // Send packet
            server.broadcast(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                             {static_cast<float>(wallId), posX, posY});
        }
    }
} // namespace ECS
