#include "SingleRequestListener.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "NetworkHandler.hpp"

SingleRequestListener::SingleRequestListener(boost::asio::io_context &aIoContext, udp::socket &aSocket,
                                             NetworkHandler *aNetworkHandler)
    : _buffer(),
      _networkHandler(aNetworkHandler)
{
    aSocket.async_receive_from(boost::asio::buffer(_buffer), _remoteEndpoint,
                               boost::bind(&SingleRequestListener::receiveRequest, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
    aIoContext.run();
}

void SingleRequestListener::receiveRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
{
    (void) aError;
    (void) aBytesTransferred;

    std::string result(_buffer.data(), aBytesTransferred);
    std::cout << "Received " << result << " from " << _remoteEndpoint << std::endl;
    _networkHandler->listen();
    delete this;
}
