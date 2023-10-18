#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "Timer+SpawnEnemy.hpp"

namespace ECS {
    void System::spawnEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::HitBox> &aHitBox,
                            Core::SparseArray<Component::IsAlive> &aIsAlive,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        Timer::TimerSpawnEnemy &timer = Timer::TimerSpawnEnemy::getInstance();
        auto &world = Core::World::getInstance();

        // Handle timer
        timer.add(world.getDeltaTime());
        if (timer.get() < ENEMY_SPAWN_INTERVAL) {
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
        aHitBox.insertAt(enemyId,
                         Component::HitBox {static_cast<float>(ENEMY_TEX_WIDTH), static_cast<float>(ENEMY_TEX_HEIGHT)});
        aIsAlive.insertAt(enemyId, Component::IsAlive {true, 0});

        // Send packet
        std::vector<float> payload = {static_cast<float>(enemyId), posX, posY};
        server.broadcast(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN), payload, aConnection);
    }
} // namespace ECS
