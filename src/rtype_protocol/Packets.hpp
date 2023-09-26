#include <any>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ClientGameEvent.hpp"
#include "ServerGameEvent.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#ifndef PACKETS_HPP
    #define PACKETS_HPP

namespace RTypeProtocol {

    struct ServerToClientPacket
    {
            ClientEventType header;
            std::size_t id;
            std::vector<float> body;

            template<typename archive>
            void serialize(archive &ar, const unsigned int /*version*/)
            {
                ar &header;
                ar &id;
                ar &body;
            }
    };

    struct ClientToServerPacket
    {
            ServerEventType header;

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
