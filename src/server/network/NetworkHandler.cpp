#include <iostream>
#include "NetworkHandler.hpp"
#include "SingleRequestListener.hpp"

using boost::asio::ip::udp;

NetworkHandler::NetworkHandler(const unsigned short aPort)
    : _port(aPort),
      _socket(udp::socket(_ioContext, udp::endpoint(udp::v4(), aPort)))
{
    std::cout << "Server listening on port " << _port << std::endl;
    listen();
}

// void handler(const boost::system::error_code &error, std::size_t bytes_transferred)
// {
//     std::cout << "HANDLER" << std::endl;
// }

void NetworkHandler::listen()
{
    try {
        SingleRequestListener listener = SingleRequestListener(_ioContext, _socket);
        // boost::array<char, 1> recvBuf;
        // udp::endpoint remoteEndpoint;

        //_socket.receive_from(boost::asio::buffer(recvBuf), remoteEndpoint);
        // bool alreadyIn = _clients.find(remoteEndpoint) != _clients.end();
        // std::count(_clients.begin(), _clients.end(), remoteEndpoint) > 0;

        // if (!alreadyIn) {
        // std::cout << "New client connected: " << remoteEndpoint << std::endl;
        //_clients[remoteEndpoint] = Player(Color::RED);
        //}
    } catch (std::exception &e) {
        std::cerr << "NetworkHandler run error: " << e.what() << std::endl;
    }
}

void NetworkHandler::send(const boost::asio::const_buffer aBuffer, size_t aClientId)
{
    (void) aBuffer;
    (void) aClientId;
    try {
        // boost::system::error_code ignoredError;
        // udp::endpoint clientEndpoint = std::advance(_clients.begin(),
        // clientId)->first;//_clients.find(clientId)->first; _socket.send_to(buffer, clientEndpoint, 0, ignoredError);
        // std::cout << "Sent something to " << clientEndpoint << std::endl;
    } catch (std::exception &e) {
        std::cerr << "NetworkHandler send error: " << e.what() << std::endl;
    }
}

void NetworkHandler::triggerEvent(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Received " << bytes_transferred << " bytes" << std::endl;
    } else {
        std::cerr << "Error: " << error.message() << std::endl;
    }
    listen();
}
