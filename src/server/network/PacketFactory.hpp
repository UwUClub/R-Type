#include <iostream>
#include "ClientPackets.hpp"
#include "Serialization.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"

#ifndef PACKET_FACTORY_HPP_
    #define PACKET_FACTORY_HPP_

namespace RType {

    static Network::PacketFactory packetFactory = {
        {ServerEventType::MOVE, [](Network::Buffer &aBuffer) -> Network::IPayload * {
             return Network::Serialization::unserializePointer<Client::MovePayload>(aBuffer);
         }}};
} // namespace RType

#endif
