#include "ServerNetworkHandler.hpp"
#include <iostream>
#include <boost/bind.hpp>
//#include "SingleRequestListener.hpp"

using boost::asio::ip::udp;

ServerNetworkHandler::ServerNetworkHandler()
    : _socket(udp::socket(_ioContext, udp::endpoint(udp::v4(), _port)))
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
    _ioContext.run();
    // check if _clients map has a value
    // std::count(_clients.begin(), _clients.end(), remoteEndpoint) > 0;

    // if (!alreadyIn) {
    // std::cout << "New client connected: " << remoteEndpoint << std::endl;
    //_clients[remoteEndpoint] = Player(Color::RED);
    //}
}

void ServerNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
{
    (void) aError;
    (void) aBytesTransferred;

    std::string result(_readBuffer.data(), aBytesTransferred);
    std::cout << "Received " << result << " from " << _readEndpoint << std::endl;
    listen();
}

void ServerNetworkHandler::send(const boost::asio::const_buffer aBuffer, size_t aClientId)
{
    (void) aBuffer;
    (void) aClientId;
    try {
        // boost::system::error_code ignoredError;
        // udp::endpoint clientEndpoint = std::advance(_clients.begin(),
        // clientId)->first;//_clients.find(clientId)->first; _socket.send_to(buffer, clientEndpoint, 0, ignoredError);
        // std::cout << "Sent something to " << clientEndpoint << std::endl;
    } catch (std::exception &e) {
        std::cerr << "ServerNetworkHandler send error: " << e.what() << std::endl;
    }
}
