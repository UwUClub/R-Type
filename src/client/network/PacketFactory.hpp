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
             return Network::Serialization::unserializePayload<Server::PlayerJoinedPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_DISCONNECTION,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::PlayerLeftPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_POSITION,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::PlayerPositionPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_SHOOT,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::PlayerShotPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_BONUS,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::PlayerGotBonusPayload>(aBuffer);
         }},
        {ClientEventType::PLAYER_DEATH,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::PlayerDiedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_SPAWN,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::EnemySpawnedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_DEATH,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::EnemyDiedPayload>(aBuffer);
         }},
        {ClientEventType::ENEMY_SHOOT,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::EnemyShotPayload>(aBuffer);
         }},
        {ClientEventType::SERVER_FULL, [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Server::ServerFullPayload>(aBuffer);
         }}};
} // namespace RType

#endif
