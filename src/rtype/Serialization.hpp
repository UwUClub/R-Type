#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include "Packets.hpp"
#include "Values.hpp"
#include <unordered_map>

#ifndef SERIALIZATION_HANDLER_HPP
    #define SERIALIZATION_HANDLER_HPP

namespace Network::Serialization {

    static void serialize(boost::asio::streambuf *aBuf, const RType::Packet &aPacket)
    {
        std::ostream os(aBuf);

        os.write(aPacket.uuid.c_str(), UUID_LENGTH);
        int type = aPacket.type;
        os.write(static_cast<const char *>(static_cast<const void *>(&type)), sizeof(type));
        for (auto &i : aPacket.payload) {
            float f = i;
            os.write(static_cast<const char *>(static_cast<const void *>(&f)), sizeof(f));
        }
    }

    static void unserialize(RType::Packet *aPacket, boost::asio::streambuf &aBuf)
    {
        std::istream is(&aBuf);

        if (aBuf.size() < 40) {
            throw std::runtime_error("Packet too small");
        }

        // Read uuid
        char uuid[UUID_LENGTH + 1] = {};
        is.read(uuid, UUID_LENGTH);
        uuid[UUID_LENGTH] = '\0';
        std::string strUuid = std::string(uuid);

        // Check invalid uuid
        if (boost::uuids::string_generator()(strUuid).version() == boost::uuids::uuid::version_unknown) {
            throw std::runtime_error("Invalid uuid");
        }
        (*aPacket).uuid = strUuid;

        // Read type
        int type = -2;
        is.read(static_cast<char *>(static_cast<void *>(&type)), sizeof(int));
        (*aPacket).type = type;

        // Read payload
        while (is.peek() != EOF) {
            float i;
            is.read(static_cast<char *>(static_cast<void *>(&i)), sizeof(float));
            (*aPacket).payload.push_back(i);
        }
    }

} // namespace Network::Serialization

#endif
