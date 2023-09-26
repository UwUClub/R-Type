#include "ServerNetworkHandler.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include "Event/EventManager.hpp"
#include "Packets.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace Network {

    using boost::asio::ip::udp;

    ServerNetworkHandler::ServerNetworkHandler(std::string &aHost, unsigned short aPort)
        : _socket(_ioService),
          _readBuffer()
    {
        boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);
        _socket.open(endpoint.protocol());
        _socket.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
        listen();
    }

    void ServerNetworkHandler::listen()
    {
        _readEndpoint = udp::endpoint();

        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                   boost::bind(&ServerNetworkHandler::handleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = std::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void ServerNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        RTypeProtocol::ClientToServerPacket packet =
            RTypeProtocol::unserializePacket<RTypeProtocol::ClientToServerPacket, std::array<char, READ_BUFFER_SIZE>>(
                _readBuffer);
        std::cout << "Received header " << static_cast<int>(packet.header) << " from " << _readEndpoint << std::endl;

        RTypeProtocol::ServerGameEvent *evt = new RTypeProtocol::ServerGameEvent(packet.header, 42);
        ECS::Event::EventManager::getInstance()->pushEvent(evt);

        // --- CONNECT event case ---
        // size_t id = 42; // temporary
        // if (_clients.find(id) == _clients.end()) {
        //     std::cout << "New client connected: " << _readEndpoint << " (id " << id << ")" << std::endl;
        //     _clients[id] = _readEndpoint;

        //     send(boost::asio::buffer("Welcome to the server!"), id);
        //     send(boost::asio::buffer("How are you ?"), id);
        // }
        // --------------------------
        listen();
    }

    void ServerNetworkHandler::send(const RTypeProtocol::ServerToClientPacket &aPacket, size_t aClientId)
    {
        try {
            udp::endpoint clientEndpoint = _clients[aClientId];

            boost::asio::streambuf buf;
            serializePacket<const RTypeProtocol::ServerToClientPacket &>(&buf, aPacket);
            _socket.send_to(buf.data(), clientEndpoint);
            std::cout << "Sent a request to " << clientEndpoint << " (id " << aClientId << ")" << std::endl;
        } catch (std::exception &e) {
            std::cerr << "ServerNetworkHandler send error: " << e.what() << std::endl;
        }
    }

    void ServerNetworkHandler::stop()
    {
        _ioService.stop();
        _socket.close();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
