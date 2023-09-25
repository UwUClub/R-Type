#include "ClientNetworkHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <string>

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

    void ClientNetworkHandler::stop()
    {
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
