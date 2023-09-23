#include "ServerNetworkHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <algorithm>

namespace Network {

    using boost::asio::ip::udp;

    void startIoService(boost::asio::io_context &aIoContext) {
        aIoContext.run();
    }

    ServerNetworkHandler::ServerNetworkHandler()
        : _socket(udp::socket(_ioContext, udp::endpoint(udp::v4(), _port)))
    {
        std::cout << "Server listening on port " << _port << std::endl;
        _ioThread = std::thread(startIoService, std::ref(_ioContext));
        listen();
    }

    ServerNetworkHandler::~ServerNetworkHandler()
    {
        _ioContext.stop();
        _ioThread.join();
    }

    void ServerNetworkHandler::listen()
    {
        _readEndpoint = udp::endpoint();

        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                boost::bind(&ServerNetworkHandler::handleRequest, this, boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
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

}
