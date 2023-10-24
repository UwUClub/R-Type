#include <iostream>
#include "ClientGameEvent.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "ServerHandler.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::enemyShoot(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::HitBox> &aHitBox,
                            Core::SparseArray<Component::IsAlive> &aIsAlive,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        auto &server = Network::ServerHandler::getInstance();
        auto &world = Core::World::getInstance();
        const auto size = aPos.size();

        for (size_t idx = 0; idx < size; idx++) {
            if (!aPos[idx].has_value() || !aType[idx].has_value() || !aIsAlive[idx].has_value()) {
                continue;
            }

            auto pos = aPos[idx].value();
            auto &type = aType[idx].value();
            auto &isAlive = aIsAlive[idx].value();

            if (type.isEnemy && rand() % PROBABILTY_SHOOT_ENEMY == 0 && isAlive.isAlive) {
                unsigned short missileId = world.createEntity();
                auto posX = pos.x - MISSILES_TEX_WIDTH;
                auto posY = pos.y + ENEMY_TEX_HEIGHT / 2.0F - MISSILES_TEX_HEIGHT / 2.0F;
                ECS::Utils::Vector2f entityPos(posX, posY);

                aPos.insertAt(missileId, entityPos);
                aSpeed.insertAt(missileId, Component::Speed {MISSILES_SPEED});
                aType.insertAt(missileId, Component::TypeEntity {false, false, false, true, false, false, false});
                aHitBox.insertAt(missileId, Component::HitBox {MISSILES_TEX_WIDTH, MISSILES_TEX_HEIGHT});

                // Send packet
                RType::Server::EnemyShotPayload payload(missileId, posX, posY);
                server.broadcast(RType::ClientEventType::ENEMY_SHOOT, payload, aConnection);
            }
        }
    }
} // namespace ECS
