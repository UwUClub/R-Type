#include <boost/asio.hpp>
#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
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

    using boost::asio::ip::udp;

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
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RType::ServerEventType::CONNECT) {
                if (server.isFull()) {
                    udp::endpoint cliEndpoint = gameEvent.getClientEndpoint();
                    network.send(RType::Packet(static_cast<int>(RType::ClientEventType::SERVER_FULL)), cliEndpoint);
                    eventManager->removeEvent(event);
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

                std::cout << "Welcome " << playerId << " !" << std::endl;

                std::vector<float> payload = {static_cast<float>(playerId), 0, static_cast<float>(playerColor), 10, 10};
                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN), payload, aConnection);
                server.addClient(playerId, gameEvent.getClientEndpoint());
                server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                          {static_cast<float>(playerId), 1, static_cast<float>(playerColor), 10, 10}),
                            playerId, aConnection);

                int aPosSize = aPos.size();
                for (std::size_t i = 0; i < aPosSize; i++) {
                    if (!aType[i].has_value() || !aPos[i].has_value()) {
                        continue;
                    }
                    if (i != playerId && aType[i]->isPlayer) {
                        float color = static_cast<float>(server.getClientColor(i));
                        server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                                  {static_cast<float>(i), 0, color, aPos[i]->x, aPos[i]->y}),
                                    playerId, aConnection);
                    }
                    if (aType[i]->isEnemy) {
                        server.send(RType::Packet(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                                                  {static_cast<float>(i), aPos[i]->x, aPos[i]->y}),
                                    playerId, aConnection);
                    }
                }

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
