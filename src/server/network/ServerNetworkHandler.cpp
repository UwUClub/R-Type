#include "ServerNetworkHandler.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <iostream>

namespace Network {

    using boost::asio::ip::udp;

    ServerNetworkHandler::ServerNetworkHandler(unsigned short aPort)
        : _port(aPort),
          _socket(udp::socket(_ioService, udp::endpoint(udp::v4(), aPort))),
          _readBuffer()
    {
        std::cout << "Server listening on port " << _port << std::endl;
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

        std::string result(_readBuffer.data(), aBytesTransferred);
        std::cout << "Received " << result << " from " << _readEndpoint << std::endl;

        // --- CONNECT event case ---
        size_t id = 42; // temporary
        if (_clients.find(id) == _clients.end()) {
            std::cout << "New client connected: " << _readEndpoint << " (id " << id << ")" << std::endl;
            _clients[id] = _readEndpoint;

            send(boost::asio::buffer("Welcome to the server!"), id);
            send(boost::asio::buffer("How are you ?"), id);
        }
        // --------------------------
        listen();
    }

    void ServerNetworkHandler::send(const boost::asio::const_buffer aBuffer, size_t aClientId)
    {
        try {
            boost::system::error_code ignoredError;
            udp::endpoint clientEndpoint = _clients[aClientId];
            _socket.send_to(aBuffer, clientEndpoint, 0, ignoredError);
            std::cout << "Sent a request to " << clientEndpoint << " (id " << aClientId << ")" << std::endl;
        } catch (std::exception &e) {
            std::cerr << "ServerNetworkHandler send error: " << e.what() << std::endl;
        }
    }

    void ServerNetworkHandler::stop()
    {
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
