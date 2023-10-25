#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "EwECS/Physic/HitBox.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "PlayerColor.hpp"
#include "ServerGameEvent.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::welcomePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                               Core::SparseArray<Component::TypeEntity> &aType,
                               Core::SparseArray<Component::HitBox> &aHitBox,
                               Core::SparseArray<Component::IsAlive> &aIsAlive,
                               Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        ECS::Network::ServerHandler &server = ECS::Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::CONNECT) {
                continue;
            }

            const auto entityId = gameEvent.getEntityId();

            if (entityId > 0 || server.isFull()) {
                server.sendError(entityId);
                toRemove.push_back(i);
                continue;
            }

            auto playerId = world.createEntity();
            RType::PLAYER_COLOR playerColor = RType::PLAYER_COLOR::BLUE; // server.addClientColor(playerId);

            if (playerColor == RType::PLAYER_COLOR::NONE) {
                world.killEntity(playerId);
                toRemove.push_back(i);
                continue;
            }

            aPos.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
            aSpeed.insertAt(playerId, Component::Speed {PLAYER_SPEED});
            aType.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false, false});
            aHitBox.insertAt(playerId, Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
            aIsAlive.insertAt(playerId, Component::IsAlive {true, 0});
            aConnection.insertAt(playerId, Component::Connection {ECS::Network::ConnectionStatus::CONNECTED});

            RType::Server::PlayerJoinedPayload payloadToBroadcast(playerId, false, playerColor, 10, 10);

            server.broadcast<RType::Server::PlayerJoinedPayload>(RType::ClientEventType::PLAYER_SPAWN,
                                                                 payloadToBroadcast, aConnection);
            server.addClient(playerId);

            RType::Server::PlayerJoinedPayload payload(playerId, true, playerColor, 10, 10);
            server.send(RType::ClientEventType::PLAYER_SPAWN, payload, playerId, aConnection);

            const auto posSize = aPos.size();
            for (size_t idx = 0; idx < posSize; idx++) {
                if (!aType[idx].has_value() || !aPos[idx].has_value()) {
                    continue;
                }

                auto &type = aType[idx].value();
                auto &pos = aPos[idx].value();

                if (idx != playerId && type.isPlayer) {
                    RType::PLAYER_COLOR color = RType::PLAYER_COLOR::RED; // TODO get color

                    RType::Server::PlayerJoinedPayload playersPayload(idx, false, color, pos.x, pos.y);
                    server.send(RType::ClientEventType::PLAYER_SPAWN, playersPayload, playerId, aConnection);
                }
                if (type.isEnemy) {
                    RType::Server::EnemySpawnedPayload enemiesPayload(idx, pos.x, pos.y);
                    server.send(RType::ClientEventType::ENEMY_SPAWN, enemiesPayload, playerId, aConnection);
                }
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
