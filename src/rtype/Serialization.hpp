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

    template<typename T>
    std::vector<uint8_t> serialize(T &data)
    {
        std::vector<uint8_t> bytes(sizeof(T));

        std::memcpy(bytes.data(), &data, sizeof(T));
        return bytes;
    }

    template<typename T>
    T unserialize(std::vector<uint8_t> &bytes)
    {
        T data;
        try {
            if (bytes.size() < sizeof(T)) {
                throw std::runtime_error("Invalid byte size for deserialization");
            }
            std::memcpy(&data, bytes.data(), sizeof(T));
        } catch (std::exception &e) {
            std::cout << "unpack error: " << e.what() << std::endl;
            throw e;
        }
        return data;
    }

    template<typename T>
    IPayload *unserializePayload(std::vector<uint8_t> &bytes)
    {
        T *data = new T;
        try {
            if (bytes.size() != sizeof(T)) {
                throw std::runtime_error("Invalid byte size for deserialization");
            }
            std::memcpy(data, bytes.data(), sizeof(T));
        } catch (std::exception &e) {
            std::cout << "unpack error: " << e.what() << std::endl;
            throw e;
        }
        return data;
    }

} // namespace Network::Serialization

#endif
