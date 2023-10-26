#include <any>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ClientGameEvent.hpp"
#include "ServerGameEvent.hpp"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#ifndef PACKETS_HPP
    #define PACKETS_HPP

namespace RType {

    struct Packet
    {
            std::string uuid;
            int type;
            std::vector<float> payload;

            Packet() = default;

            Packet(int aType)
                : uuid(boost::uuids::to_string(boost::uuids::uuid(boost::uuids::random_generator()()))),
                  type(aType),
                  payload()
            {}

            Packet(int aType, std::vector<float> aPayload)
                : uuid(boost::uuids::to_string(boost::uuids::uuid(boost::uuids::random_generator()()))),
                  type(aType),
                  payload(aPayload)
            {}

            Packet(std::string &aUuid, int aType)
                : uuid(aUuid),
                  type(aType)
            {}
    };

    struct Aknowlegdment
    {
            std::string uuid;
    };
} // namespace RType

#endif
