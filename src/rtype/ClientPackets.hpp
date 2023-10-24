#include "Packet.hpp"

#ifndef CLIENTPACKETS_HPP
    #define CLIENTPACKETS_HPP

namespace RType::Client {

    struct ConnectPayload : Network::IPayload
    {};

    struct DisconnectPayload : Network::IPayload
    {};

    struct MovePayload : Network::IPayload
    {
            float moveX;
            float moveY;

            explicit MovePayload(float aMoveX, float aMoveY)
                : moveX(aMoveX),
                  moveY(aMoveY)
            {}
    };

    struct ShootPayload : Network::IPayload
    {};

} // namespace RType::Client

#endif
