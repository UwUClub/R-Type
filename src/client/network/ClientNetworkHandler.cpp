#include "ClientNetworkHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <string>
#include "Packets.hpp"
#include <boost/archive/binary_oarchive.hpp>

namespace Network {

    using boost::asio::ip::udp;

    ClientNetworkHandler::ClientNetworkHandler(std::string &aHost, std::string &aPort)
        : _resolver(udp::resolver(_ioService)),
          _socket(udp::socket(_ioService)),
          _readBuffer()
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

        RTypeProtocol::ServerToClientPacket packet =
            RTypeProtocol::unserializePacket<RTypeProtocol::ServerToClientPacket, std::array<char, READ_BUFFER_SIZE>>(
                _readBuffer);
        std::cout << "Received header " << static_cast<int>(packet.header) << " from " << _serverEndpoint << std::endl;
        listen();
    }

    void ClientNetworkHandler::send(const RTypeProtocol::ClientToServerPacket &aPacket)
    {
        try {
            boost::asio::streambuf buf;
            serializePacket<const RTypeProtocol::ClientToServerPacket &>(&buf, aPacket);
            _socket.send_to(buf.data(), _serverEndpoint);
            std::cout << "Sent something to " << _serverEndpoint << std::endl;
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
