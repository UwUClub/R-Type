#include "ClientNetworkHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <string>

namespace Network {

    constexpr std::string_view HOST = "127.0.0.1";

    using boost::asio::ip::udp;

    ClientNetworkHandler::ClientNetworkHandler()
        : _resolver(udp::resolver(_ioContext)),
        _socket(udp::socket(_ioContext))
    {
        _serverEndpoint = *_resolver.resolve(udp::v4(), HOST, "daytime").begin();
        _socket.open(udp::v4());
        std::cout << "Connected to " << _serverEndpoint << std::endl;
    }

    void ClientNetworkHandler::listen()
    {
        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _serverEndpoint,
                                    boost::bind(&ClientNetworkHandler::handleRequest, this, boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        _ioContext.run();
    }

    void ClientNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        std::string result(_readBuffer.data(), aBytesTransferred);
        std::cout << "Received " << result << " from server" << std::endl;
        listen();
    }

    void ClientNetworkHandler::send(const boost::asio::const_buffer &buffer)
    {
        try {
            _socket.send_to(boost::asio::buffer(buffer), _serverEndpoint);
            std::cout << "Sent something to " << _serverEndpoint << std::endl;
        } catch (std::exception &e) {
            std::cerr << "ClientNetworkHandler send error: " << e.what() << std::endl;
        }
    }

}
