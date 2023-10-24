#include "NetworkHandler.hpp"
#include <boost/bind.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include "Serialization.hpp"
#include "Values.hpp"

namespace Network {

    using boost::asio::ip::udp;

    void NetworkHandler::start(const boost::asio::basic_socket<boost::asio::ip::udp>::protocol_type &aProtocol)
    {
        _socket.open(aProtocol);
        listen();
    }

    void NetworkHandler::bind(const udp::endpoint &aEndpoint)
    {
        _socket.bind(aEndpoint);
    }

    void NetworkHandler::onReceive(ReceiveCallback aOnReceive)
    {
        _onReceive = aOnReceive;
    }

    void NetworkHandler::listen()
    {
        _readBuffer = _readInbound.prepare(READ_BUFFER_SIZE);
        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                   boost::bind(&NetworkHandler::tryHandleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    template<typename T>
    std::vector<uint8_t> myPack(T &data)
    {
        std::vector<uint8_t> bytes(sizeof(T));
        // auto *src = static_cast<uint8_t *>(static_cast<void *>(&data));
        // std::copy(src, src + sizeof(T), std::back_inserter(dst));
        std::memcpy(bytes.data(), &data, sizeof(T));
        return bytes;
    }

    template<typename T>
    T myUnpack(std::vector<uint8_t> &bytes)
    {
        try {
            if (bytes.size() != sizeof(T)) {
                throw std::runtime_error("Invalid byte size for deserialization");
            }
            T data;
            std::memcpy(&data, bytes.data(), sizeof(T));
            return data;
        } catch (std::exception &e) {
            std::cout << "unpack error: " << e.what() << std::endl;
        }
    }

    void NetworkHandler::tryHandleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;

        try {
            _readInbound.commit(aBytesTransferred);
            auto buff = Buffer(boost::asio::buffers_begin(_readInbound.data()),
                               boost::asio::buffers_begin(_readInbound.data()) + aBytesTransferred);
            auto header = myUnpack<PacketHeader>(buff);
            auto payload = _packetFactory[header.type](buff);

            if (header.type == -1) { // receive aknowledgment
                if (_senders.find(header.uuid) != _senders.end() && _senders[header.uuid].first.joinable()) {
                    _senders[header.uuid].second = false;
                    _senders[header.uuid].first.join();
                    _senders.erase(header.uuid);
                }
            } else if (header.type >= 0) { // send aknowledgment
                // IPacket aknowledgment(header.uuid, AKNOWLEDGMENT_PACKET_TYPE);
                // send(aknowledgment, _readEndpoint);
            }
            _onReceive(header.type, payload, _readEndpoint);
        } catch (const std::exception &e) {
            send(ERROR_PACKET_TYPE, _readEndpoint);
            std::cout << "unserialization error: " << e.what() << std::endl;
        }
        _readInbound.consume(_readInbound.size());
        listen();
    }

    void NetworkHandler::handleRequest(std::size_t aBytesTransferred)
    {}

    void NetworkHandler::send(int8_t aType, const udp::endpoint &aEndpoint)
    {
        PacketHeader header(aType);

        std::vector<uint8_t> strBuff = myPack(header); // Network::Serialization::serialize(header);
        _socket.send_to(boost::asio::buffer(strBuff), aEndpoint);
    }

    boost::asio::io_service &NetworkHandler::getIoService()
    {
        return _ioService;
    }

    void NetworkHandler::stop()
    {
        for (auto &sender : _senders) {
            sender.second.second = false;
            if (sender.second.first.joinable()) {
                sender.second.first.join();
            }
        }
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
        _socket.close();
    }

} // namespace Network
