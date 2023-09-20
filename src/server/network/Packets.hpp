#include <any>
#include <vector>
#include "GameEvent.hpp"

#ifndef PACKETS_HPP
    #define PACKETS_HPP

enum class PacketToSendType
{
    PLAYER_CONNECTION = 0,
    PLAYER_DISCONNECTION = 1,
    PLAYER_POSITION = 2,
    PLAYER_SHOOT = 3,
    PLAYER_HEALTH = 4,
    PLAYER_DEATH = 5,
    MONSTER_SPAWN = 6,
    MONSTER_DEATH = 7,
    MONSTER_POSITION = 8,
    MONSTER_SHOOT = 9,
};

struct PacketToSend
{
        PacketToSendType type;
};

struct ReceivedPacket
{
        Game::ClientEvent type;
        std::any body;
};

#endif
