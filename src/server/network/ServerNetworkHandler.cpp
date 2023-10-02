#include "ServerNetworkHandler.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "Packets.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace Network {

    using boost::asio::ip::udp;

    ServerNetworkHandler::ServerNetworkHandler()
        : _socket(_ioService),
          _readBuffer()
    {}

    void ServerNetworkHandler::start(std::string &aHost, unsigned short aPort)
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

        RTypeProtocol::ClientToServerPacket packet;
        RTypeProtocol::unserializePacket<RTypeProtocol::ClientToServerPacket, std::array<char, READ_BUFFER_SIZE>>(
            &packet, _readBuffer);

        auto client =
            std::find_if(_clients.begin(), _clients.end(), [this](const std::pair<size_t, udp::endpoint> &aPair) {
                return aPair.second == _readEndpoint;
            });

        if (client == _clients.end() && packet.type == RTypeProtocol::ServerEventType::CONNECT) {
            ECS::Event::EventManager::getInstance()->pushEvent(
                new RTypeProtocol::ServerGameEvent(RTypeProtocol::ServerEventType::CONNECT, 0, _readEndpoint));
        }
        if (client != _clients.end() && packet.type != RTypeProtocol::ServerEventType::CONNECT) {
            size_t id = client->first;
            auto *evt = new RTypeProtocol::ServerGameEvent(packet.type, id, _readEndpoint);

            ECS::Event::EventManager::getInstance()->pushEvent(evt);
        }
        listen();
    }

    void ServerNetworkHandler::addClient(std::size_t aClientId, udp::endpoint aEndpoint)
    {
        _clients[aClientId] = aEndpoint;
        std::cout << "Player " << aClientId << " joined" << std::endl;
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
