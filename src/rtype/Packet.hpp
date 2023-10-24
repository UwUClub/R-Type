#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <string>
#include "boost/uuid/uuid_io.hpp"
#include <boost/uuid/uuid_generators.hpp>

#ifndef PACKETS_HPP
    #define PACKETS_HPP

namespace Network {

    struct PacketHeader
    {
            std::string uuid;
            int8_t type;

            PacketHeader() = default;

            PacketHeader(uint8_t aType)
                : uuid(boost::uuids::to_string(boost::uuids::uuid(boost::uuids::random_generator()()))),
                  type(aType)
            {}
    };

    struct IPayload
    {};

    struct Aknowlegdment
    {
            std::string uuid;
    };
} // namespace Network

#endif
