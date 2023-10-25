#include <iostream>
#include "ClientPackets.hpp"
#include "Serialization.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"

#ifndef PACKET_FACTORY_HPP_
    #define PACKET_FACTORY_HPP_

namespace RType {

    static Network::PacketFactory packetFactory = {
        {ServerEventType::CONNECT,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return nullptr;
         }},
        {ServerEventType::DISCONNECT,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return nullptr;
         }},
        {ServerEventType::MOVE,
         [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePayload<Client::MovePayload>(aBuffer);
         }},
        {ServerEventType::SHOOT, [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return nullptr;
         }}};
} // namespace RType

#endif
