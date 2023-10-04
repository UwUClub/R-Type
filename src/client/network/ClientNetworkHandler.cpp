#include "ClientNetworkHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include "EventManager.hpp"
#include "Packets.hpp"

namespace Network {

    using boost::asio::ip::udp;

    void ClientNetworkHandler::start(std::string &aHost, std::string &aPort)
    {
        _serverEndpoint = *_resolver.resolve(udp::v4(), aHost, aPort).begin();
        _socket.open(udp::v4());
        std::cout << "Connected to " << _serverEndpoint << std::endl;
        listen();
    }

    void ClientNetworkHandler::listen()
    {
        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _serverEndpoint,
                                   boost::bind(&ClientNetworkHandler::handleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = std::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void ClientNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        RTypeProtocol::Packet packet;
        RTypeProtocol::unserializePacket<std::array<char, READ_BUFFER_SIZE>>(&packet, _readBuffer);
        // std::cout << "Received type " << static_cast<int>(packet.type) << " from " << _serverEndpoint << std::endl;

        auto *evt = new RTypeProtocol::ClientGameEvent(packet.type, 0, packet.payload);
        ECS::Event::EventManager::getInstance()->pushEvent(evt);

        listen();
    }

    void ClientNetworkHandler::send(const RTypeProtocol::Packet &aPacket)
    {
        try {
            boost::asio::streambuf buf;
            RTypeProtocol::serializePacket(&buf, aPacket);
            _socket.send_to(buf.data(), _serverEndpoint);
            // std::cout << "Sent something to " << _serverEndpoint << std::endl;
        } catch (std::exception &e) {
            std::cerr << "ClientNetworkHandler send error: " << e.what() << std::endl;
        }
    }

    void ClientNetworkHandler::stop()
    {
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
