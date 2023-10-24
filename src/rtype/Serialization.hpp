#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <strstream>
#include "Packet.hpp"
#include "Values.hpp"
#include "boost/uuid/string_generator.hpp"
#include <unordered_map>

#ifndef SERIALIZATION_HANDLER_HPP
    #define SERIALIZATION_HANDLER_HPP

namespace Network::Serialization {

    static std::vector<uint8_t> serialize(PacketHeader &header)
    {
        std::vector<uint8_t> bytes(sizeof(header));
        auto ptr = reinterpret_cast<uint8_t *>(&header);
        auto it = bytes.begin();

        // Serialize header
        std::copy(ptr, ptr + sizeof(header.uuid), it);
        it += sizeof(header.uuid);
        std::copy(ptr, ptr + sizeof(header.type), it);
        it += sizeof(header.type);

        return bytes;
    }

    template<typename Payload>
    static std::vector<uint8_t> serialize(PacketHeader &header, Payload &payload)
    {
        std::vector<uint8_t> bytes(sizeof(header) + sizeof(Payload));
        auto headerPtr = reinterpret_cast<uint8_t *>(&header);
        auto payloadPtr = reinterpret_cast<uint8_t *>(&payload);
        auto it = bytes.begin();

        // Serialize header
        std::copy(headerPtr, headerPtr + sizeof(header.uuid), it);
        it += sizeof(header.uuid);
        std::copy(headerPtr, headerPtr + sizeof(header.type), it);
        it += sizeof(header.type);

        // Serialize payload
        std::copy(payloadPtr, payloadPtr + sizeof(Payload), it);

        return bytes;
    }

    static PacketHeader &unserializeHeader(const std::vector<uint8_t> &bytes)
    {
        PacketHeader header;
        auto ptr = reinterpret_cast<uint8_t *>(&header);
        auto it = bytes.begin();

        // Check packet size
        if (bytes.size() < sizeof(PacketHeader)) {
            throw std::runtime_error("Packet too small");
        }

        // Unserialize header
        std::copy(it, it + sizeof(header.uuid), ptr);
        it += sizeof(header.uuid);
        std::copy(it, it + sizeof(header.type), ptr);
        it += sizeof(header.type);

        return header;
    }

    template<typename T>
    static T &unserializePayload(std::vector<uint8_t> &bytes)
    {
        T payload;
        auto ptr = reinterpret_cast<uint8_t *>(&payload);
        auto it = bytes.begin();

        // Check packet size
        if (bytes.size() < sizeof(T)) {
            throw std::runtime_error("Packet too small");
        }

        // Unserialize payload
        std::copy(it, it + sizeof(T), ptr);

        return payload;
    }

    // static void serialize(boost::asio::streambuf *aBuf, const PacketHeader &aHeader, const IPacket &aPacket)
    // {
    //     std::vector<uint8_t> bytes(aHeader.size() + aPacket.size());

    //     std::ostream os(aBuf);

    //     // Serialize header
    //     os.write(aHeader.uuid.c_str(), UUID_LENGTH);
    //     int type = aHeader.type;
    //     os.write(static_cast<const char *>(static_cast<const void *>(&type)), sizeof(type));

    //     // Convert aPacket to a vector of bytes
    //     std::vector<uint8_t> packetBytes = aPacket.serialize();
    //     os.write(reinterpret_cast<const char *>(packetBytes.data()), packetBytes.size());
    // }

    // static void unserialize(RType::Packet *aPacket, boost::asio::streambuf &aBuf)
    // {
    //     std::istream is(&aBuf);

    //     if (aBuf.size() < 40) {
    //         throw std::runtime_error("Packet too small");
    //     }

    //     // Read uuid
    //     char uuid[UUID_LENGTH + 1] = {};
    //     is.read(uuid, UUID_LENGTH);
    //     uuid[UUID_LENGTH] = '\0';
    //     std::string strUuid = std::string(uuid);

    //     // Check invalid uuid
    //     if (boost::uuids::string_generator()(strUuid).version() == boost::uuids::uuid::version_unknown) {
    //         throw std::runtime_error("Invalid uuid");
    //     }
    //     (*aPacket).uuid = strUuid;

    //     // Read type
    //     int type = -2;
    //     is.read(static_cast<char *>(static_cast<void *>(&type)), sizeof(int));
    //     (*aPacket).type = type;

    //     // Read payload
    //     while (is.peek() != EOF) {
    //         float i;
    //         is.read(static_cast<char *>(static_cast<void *>(&i)), sizeof(float));
    //         (*aPacket).payload.push_back(i);
    //     }
    // }

    // static PacketHeader &unserializeHeader(std::vector<uint8_t> &aBuf)
    // {
    //     PacketHeader header;
    //     std::istrstream is(reinterpret_cast<const char *>(aBuf.data(), aBuf.size()));

    //     if (aBuf.size() < 40) {
    //         throw std::runtime_error("Packet too small");
    //     }

    //     // Read uuid
    //     char uuid[UUID_LENGTH + 1] = {};
    //     is.read(uuid, UUID_LENGTH);
    //     uuid[UUID_LENGTH] = '\0';
    //     std::string strUuid = std::string(uuid);

    //     // Check invalid uuid
    //     if (boost::uuids::string_generator()(strUuid).version() == boost::uuids::uuid::version_unknown) {
    //         throw std::runtime_error("Invalid uuid");
    //     }
    //     header.uuid = strUuid;

    //     // Read type
    //     int type = -2;
    //     is.read(static_cast<char *>(static_cast<void *>(&type)), sizeof(int));
    //     header.type = type;

    //     return header;
    // }

} // namespace Network::Serialization

#endif
