#include <cstddef>
#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "EwECS/World.hpp"
#include "ServerGameEvent.hpp"
#include "ServerPackets.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::triggerBonus(Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::IsAlive> &aIsAlive,
                              Core::SparseArray<Component::HitBox> &aHitBox,
                              Core::SparseArray<Component::Connection> &aConnection,
                              Core::SparseArray<Component::Speed> &aSpeed)
    {
        auto &world = Core::World::getInstance();
        auto &server = Network::ServerHandler::getInstance();
        const auto size = aType.size();

        for (size_t playerId = 0; playerId < size; playerId++) {
            if (!aType[playerId].has_value() || !aType[playerId].value().isPlayer || !aHitBox[playerId].has_value()
                || !aIsAlive[playerId].has_value()) {
                continue;
            }

            auto &hitBoxPlayer = aHitBox[playerId].value();
            auto &isPlayerAlive = aIsAlive[playerId].value();

            if (!isPlayerAlive.isAlive) {
                continue;
            }

            if (!hitBoxPlayer.isColliding) {
                continue;
            }

            auto &colliders = hitBoxPlayer.collidingId;

            for (auto &collider : colliders) {
                if (!aType[collider].has_value() || !aType[collider].value().isBonus) {
                    continue;
                }

                aSpeed[playerId].value().speed *= BONUS_GAIN_FACTOR;

                RType::Server::PlayerGotBonusPayload payload(playerId, collider);
                server.broadcast(RType::ClientEventType::PLAYER_BONUS, payload, aConnection);
                world.killEntity(collider);
            }
        }
    }
} // namespace ECS
