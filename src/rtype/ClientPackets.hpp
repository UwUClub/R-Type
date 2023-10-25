#include "Packet.hpp"

#ifndef CLIENTPACKETS_HPP
    #define CLIENTPACKETS_HPP

namespace RType::Client {

    PACK(struct ConnectPayload : Network::IPayload {});

    PACK(struct DisconnectPayload : Network::IPayload {});

    PACK(struct MovePayload
         : Network::IPayload {
             float moveX;
             float moveY;

             MovePayload() = default;

             MovePayload(float aMoveX, float aMoveY)
             {
                 moveX = aMoveX;
                 moveY = aMoveY;
             }
         });

    PACK(struct ShootPayload : Network::IPayload {});

} // namespace RType::Client

#endif
