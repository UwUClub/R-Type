#include <iostream>
#include "ClientPackets.hpp"
#include "EwECS/Network/Serialization.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "ServerGameEvent.hpp"

#ifndef PACKET_FACTORY_HPP_
    #define PACKET_FACTORY_HPP_

namespace RType {

    static ECS::Network::PacketFactory packetFactory = {
        {ServerEventType::MOVE, [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
             return ECS::Network::unserializePointer<Client::MovePayload>(aBuffer);
         }}};
} // namespace RType

#endif
