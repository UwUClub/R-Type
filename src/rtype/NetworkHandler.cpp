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

    void NetworkHandler::tryHandleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;

        try {
            handleRequest(aBytesTransferred);
        } catch (const std::exception &e) {
            send(ERROR_PACKET_TYPE, _readEndpoint);
        }
        _readInbound.consume(_readInbound.size());
        listen();
    }

    void NetworkHandler::handleRequest(std::size_t aBytesTransferred)
    {
        _readInbound.commit(aBytesTransferred);
        auto buff = Buffer(boost::asio::buffers_begin(_readInbound.data()),
                           boost::asio::buffers_begin(_readInbound.data()) + aBytesTransferred);

        auto header = Network::Serialization::unserializeHeader(buff);
        buff.erase(buff.begin(), buff.begin() + sizeof(header));
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
    }

    void NetworkHandler::send(int8_t aType, const udp::endpoint &aEndpoint)
    {
        boost::asio::streambuf buf = boost::asio::streambuf();
        PacketHeader header(aType);
        auto strBuff = Network::Serialization::serialize(header);

        _socket.send_to(buf.data(), aEndpoint);
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
