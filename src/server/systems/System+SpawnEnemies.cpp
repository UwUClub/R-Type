#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "Timer+SpawnEnemies.hpp"

namespace ECS {
    void System::spawnEnemies(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                              Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::HitBox> &aHitBox,
                              Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        Timer::TimerSpawnEnemies &timer = Timer::TimerSpawnEnemies::getInstance();
        auto &world = Core::World::getInstance();

        // Handle timer
        timer.add(world.getDeltaTime());
        if (timer.get() < 1) {
            return;
        }
        timer.reset();

        // Create entity
        size_t enemyId = world.createEntity();
        float posX = static_cast<float>(SCREEN_WIDTH - ENEMY_TEX_WIDTH);
        float posY = static_cast<float>(rand() % SCREEN_HEIGHT);
        aPos.insertAt(enemyId, ECS::Utils::Vector2f {posX, posY});
        aSpeed.insertAt(enemyId, Component::Speed {ENEMY_SPEED});
        aType.insertAt(enemyId, Component::TypeEntity {false, false, true, false, false, false, false});
        aHitBox.insertAt(enemyId, Component::HitBox {ENEMY_TEX_WIDTH, ENEMY_TEX_HEIGHT});
        aIsAlive.insertAt(enemyId, Component::IsAlive {true, 0});

        // Send packet
        server.broadcast(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                         {static_cast<float>(enemyId), posX, posY});
    }
} // namespace ECS
