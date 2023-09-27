#include <any>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/array.hpp>
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
            ClientEventType type;
            std::size_t id;
            bool isYou;
            std::array<float, 2> position;

            template<typename archive>
            void serialize(archive &ar, const unsigned int /*version*/)
            {
                ar &type;
                ar &id;
                ar &isYou;
                ar &position;
            }
    };

    struct ClientToServerPacket
    {
            ServerEventType type;

            template<typename archive>
            void serialize(archive &ar, const unsigned int /*version*/)
            {
                ar &type;
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
    void unserializePacket(PacketType *aPacket, BufferType &aReadBuffer)
    {
        std::string receivedData(aReadBuffer.data(), aReadBuffer.size());
        std::istringstream archiveStream(receivedData);
        boost::archive::binary_iarchive archive(archiveStream);
        archive >> *aPacket;
    }
} // namespace RTypeProtocol

#endif
