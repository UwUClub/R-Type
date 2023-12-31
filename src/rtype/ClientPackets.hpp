#include "EwECS/Network/Packet.hpp"

#ifndef CLIENTPACKETS_HPP
    #define CLIENTPACKETS_HPP

namespace RType::Client {

    PACK(struct MovePayload
         : ECS::Network::IPayload {
             float moveX;
             float moveY;

             MovePayload() = default;

             MovePayload(float aMoveX, float aMoveY)
             {
                 moveX = aMoveX;
                 moveY = aMoveY;
             }
         });
} // namespace RType::Client

#endif
