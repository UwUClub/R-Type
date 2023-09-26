#include <any>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#ifndef PACKETS_HPP
    #define PACKETS_HPP

namespace RTypeProtocol {
    enum class ClientEvent;

    enum class ServerToClientPacketType
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

    struct ServerToClientPacket
    {
            ServerToClientPacketType header;
            std::vector<int> body;

            template<typename archive>
            void serialize(archive &ar, const unsigned int /*version*/)
            {
                ar &header;
                ar &body;
            }
    };

    struct ClientToServerPacket
    {
            ClientEvent header;

            template<typename archive>
            void serialize(archive &ar, const unsigned int /*version*/)
            {
                ar &header;
            }
    };

    template<typename PacketType>
    void serializePacket(boost::asio::streambuf *buf, PacketType &aPacket)
    {
        std::ostream archiveStream(buf);
        boost::archive::binary_oarchive archive(archiveStream);
        archive << aPacket;
    }

    template<typename PacketType, typename BufferType>
    PacketType &unserializePacket(BufferType &aReadBuffer)
    {
        std::string receivedData(aReadBuffer.data(), aReadBuffer.size());
        std::istringstream archiveStream(receivedData);
        boost::archive::binary_iarchive archive(archiveStream);
        PacketType packet;
        archive >> packet;
        return packet;
    }
} // namespace RTypeProtocol

#endif
