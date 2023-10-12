#include <boost/asio.hpp>
#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
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

    void System::welcomePlayer(RType::ServerGameEvent *aEvent)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        Network::NetworkHandler &network = Network::NetworkHandler::getInstance();
        auto &posComp = world.getComponent<ECS::Utils::Vector2f>();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &hitBoxComp = world.getComponent<Component::HitBox>();
        auto &isAliveComp = world.getComponent<Component::IsAlive>();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::CONNECT) {
            if (server.isFull()) {
                udp::endpoint cliEndpoint = aEvent->getClientEndpoint();
                network.send(RType::Packet(static_cast<int>(RType::ClientEventType::SERVER_FULL)), cliEndpoint);
                return;
            }

            size_t playerId = world.createEntity();
            RType::PLAYER_COLOR playerColor = server.addClientColor(playerId);

            if (playerColor == RType::PLAYER_COLOR::NONE) {
                world.killEntity(playerId);
                return;
            }

            posComp.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
            speedComp.insertAt(playerId, Component::Speed {PLAYER_SPEED});
            typeComp.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false, false});
            hitBoxComp.insertAt(playerId, Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
            isAliveComp.insertAt(playerId, Component::IsAlive {true, 0});
            connectionComp.insertAt(playerId, Component::Connection {Network::ConnectionStatus::CONNECTED});

            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                             {static_cast<float>(playerId), 0, static_cast<float>(playerColor), 10, 10},
                             connectionComp);
            server.addClient(playerId, aEvent->getClientEndpoint());
            server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                      {static_cast<float>(playerId), 1, static_cast<float>(playerColor), 10, 10}),
                        playerId, connectionComp);

            std::cout << "Player " << playerId << " joined" << std::endl;
            const auto aPosSize = posComp.size();
            for (std::size_t i = 0; i < aPosSize; i++) {
                if (!typeComp[i].has_value() || !posComp[i].has_value()) {
                    continue;
                }
                if (i != playerId && typeComp[i]->isPlayer) {
                    auto color = static_cast<float>(server.getClientColor(i));
                    server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                              {static_cast<float>(i), 0, color, posComp[i]->x, posComp[i]->y}),
                                playerId, connectionComp);
                }
                if (typeComp[i]->isEnemy) {
                    server.send(RType::Packet(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                                              {static_cast<float>(i), posComp[i]->x, posComp[i]->y}),
                                playerId, connectionComp);
                }
            }
        }
    }
} // namespace ECS
