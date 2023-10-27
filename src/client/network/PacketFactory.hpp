#include <iostream>
#include "ClientGameEvent.hpp"
#include "ClientHandler.hpp"
#include "Serialization.hpp"
#include "ServerPackets.hpp"

#ifndef PACKET_FACTORY_HPP_
    #define PACKET_FACTORY_HPP_

namespace RType {

    static Network::PacketFactory packetFactory = {
        {ClientEventType::PLAYER_SPAWN,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerJoinedPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_DISCONNECTION,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerLeftPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_POSITION,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerPositionPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_SHOOT,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerShotPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_BONUS,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerGotBonusPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_DEATH,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::PlayerDiedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_SPAWN,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::EnemySpawnedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_DEATH,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::EnemyDiedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_SHOOT, [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Server::EnemyShotPayload>(aBuffer);
         }}};
} // namespace RType

#endif
