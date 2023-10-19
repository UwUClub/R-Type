#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "Components.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "PlayerColor.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::welcomePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                               Core::SparseArray<Component::TypeEntity> &aType,
                               Core::SparseArray<Component::HitBox> &aHitBox,
                               Core::SparseArray<Component::IsAlive> &aIsAlive,
                               Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        Network::NetworkHandler &network = Network::NetworkHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::CONNECT) {
                continue;
            }
            if (server.isFull()) {
                const auto &cliEndpoint = gameEvent.getClientEndpoint();

                network.send(RType::Packet(static_cast<int>(RType::ClientEventType::SERVER_FULL)), cliEndpoint);
                toRemove.push_back(i);
                continue;
            }

            size_t playerId = world.createEntity();
            RType::PLAYER_COLOR playerColor = server.addClientColor(playerId);

            if (playerColor == RType::PLAYER_COLOR::NONE) {
                world.killEntity(playerId);
                continue;
            }

            aPos.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
            aSpeed.insertAt(playerId, Component::Speed {PLAYER_SPEED});
            aType.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false, false});
            aHitBox.insertAt(playerId, Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
            aIsAlive.insertAt(playerId, Component::IsAlive {true, 0});
            aConnection.insertAt(playerId, Component::Connection {Network::ConnectionStatus::CONNECTED});

            std::vector<float> payload = {static_cast<float>(playerId), 0, static_cast<float>(playerColor), 10, 10};

            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN), payload, aConnection);
            server.addClient(playerId, gameEvent.getClientEndpoint());
            server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                      {static_cast<float>(playerId), 1, static_cast<float>(playerColor), 10, 10}),
                        playerId, aConnection);

            const auto posSize = aPos.size();
            for (std::size_t idx = 0; idx < posSize; idx++) {
                if (!aType[idx].has_value() || !aPos[idx].has_value()) {
                    continue;
                }

                auto &type = aType[idx].value();
                auto &pos = aPos[idx].value();

                if (idx != playerId && type.isPlayer) {
                    auto color = static_cast<float>(server.getClientColor(idx));

                    server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                              {static_cast<float>(idx), 0, color, pos.x, pos.y}),
                                playerId, aConnection);
                }
                if (type.isEnemy) {
                    server.send(RType::Packet(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                                              {static_cast<float>(idx), pos.x, pos.y}),
                                playerId, aConnection);
                }
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
