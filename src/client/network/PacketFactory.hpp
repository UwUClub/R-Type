#include <iostream>
#include "ClientGameEvent.hpp"
#include "EwECS/Network/ClientHandler.hpp"
#include "EwECS/Network/Serialization.hpp"
#include "ServerPackets.hpp"

#ifndef PACKET_FACTORY_HPP_
    #define PACKET_FACTORY_HPP_

namespace RType {

    static ECS::Network::
        PacketFactory packetFactory = {{ClientEventType::PLAYER_SPAWN,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerJoinedPayload>(
                                                aBuffer);
                                        }},
                                       {ClientEventType::PLAYER_DISCONNECTION,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerLeftPayload>(aBuffer);
                                        }},
                                       {ClientEventType::PLAYER_POSITION,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerPositionPayload>(
                                                aBuffer);
                                        }},
                                       {ClientEventType::PLAYER_SHOOT,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerShotPayload>(aBuffer);
                                        }},
                                       {ClientEventType::PLAYER_BONUS,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerGotBonusPayload>(
                                                aBuffer);
                                        }},
                                       {ClientEventType::PLAYER_DEATH,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::PlayerDiedPayload>(aBuffer);
                                        }},
                                       {ClientEventType::ENEMY_SPAWN,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::EnemySpawnedPayload>(
                                                aBuffer);
                                        }},
                                       {ClientEventType::ENEMY_DEATH,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::EnemyDiedPayload>(aBuffer);
                                        }},
                                       {ClientEventType::ENEMY_SHOOT,
                                        [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
                                            return ECS::Network::unserializePointer<Server::EnemyShotPayload>(aBuffer);
                                        }}};
} // namespace RType

#endif
