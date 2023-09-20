#include <vector>

#ifndef PACKET_HPP
    #define PACKET_HPP

enum class PacketToSendType
{
    CONNECT = 0,
    DISCONNECT,
    CRASH,
    MOVE,
    SHOOT
};

enum class ReceivedPacketType
{
    PLAYER_CONNECTION = 0,
    PLAYER_DISCONNECTION,
    PLAYER_POSITION,
    PLAYER_SHOOT,
    PLAYER_HEALTH,
    PLAYER_DEATH,
    MONSTER_SPAWN,
    MONSTER_DEATH,
    MONSTER_POSITION,
    MONSTER_SHOOT
};

struct PacketToSend
{
        PacketToSendType type;
};

struct ReceivedPacket
{
        ReceivedPacketType type;
        std::vector<int> data;
};

#endif
