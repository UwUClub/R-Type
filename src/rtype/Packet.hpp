#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <string>
#include "Values.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <boost/uuid/uuid_generators.hpp>

#ifndef PACKETS_HPP
    #define PACKETS_HPP

namespace Network {

    #if defined(_MSC_VER)
        #define PACK(definition) __pragma(pack(push, 1)) definition __pragma(pack(pop))
    #elif defined(__GNUC__) || defined(__clang__)
        #define PACK(definition) definition __attribute__((packed))
    #else
        #error "Unknown compiler, please provide a way to align structures"
    #endif

    PACK(struct PacketHeader {
        char uuid[UUID_LENGTH + 1] = {0};
        int8_t type = 0;

        PacketHeader() = default;

        PacketHeader(uint8_t aType)
        {
            type = aType;
            std::string strUuid = boost::uuids::to_string(boost::uuids::uuid(boost::uuids::random_generator()()));

            for (int i = 0; i < UUID_LENGTH; i++) {
                uuid[i] = strUuid[i];
            }
            uuid[UUID_LENGTH] = '\0';
        }
    });
    struct IPayload
    {};

    struct Aknowlegdment
    {
            std::string uuid;
    };
} // namespace Network

#endif
