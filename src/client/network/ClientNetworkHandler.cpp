#include "ClientNetworkHandler.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace Network {

    using boost::asio::ip::udp;

    ClientNetworkHandler::ClientNetworkHandler(const std::string &host)
        : _resolver(udp::resolver(_ioContext)),
          _socket(udp::socket(_ioContext))
    {
        _serverEndpoint = *_resolver.resolve(udp::v4(), host, "daytime").begin();
        _socket.open(udp::v4());
        std::cout << "Connected to " << _serverEndpoint << std::endl;
    }

    void ClientNetworkHandler::listen()
    {
        try {
            for (;;) {
                boost::array<char, 128> recvBuf;
                udp::endpoint senderEndpoint;
                size_t len = _socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);
                std::string result(recvBuf.data(), len);
                std::cout << "Received " << result << " from " << senderEndpoint << std::endl;
            }

        } catch (std::exception &e) {
            std::cerr << "ClientNetworkHandler run error: " << e.what() << std::endl;
        }
    }

    void ClientNetworkHandler::send(const boost::asio::const_buffer &buffer)
    {
        try {
            // boost::array<char, 1> buffer  = {{ 0 }};
            _socket.send_to(boost::asio::buffer(buffer), _serverEndpoint);
            std::cout << "Sent something to " << _serverEndpoint << std::endl;
        } catch (std::exception &e) {
            std::cerr << "ClientNetworkHandler send error: " << e.what() << std::endl;
        }
    }

} // namespace Network
