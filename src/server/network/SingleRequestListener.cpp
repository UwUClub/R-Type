#include <iostream>
#include <boost/bind.hpp>
#include "SingleRequestListener.hpp"
#include "NetworkHandler.hpp"

SingleRequestListener::SingleRequestListener(boost::asio::io_context &aIoContext, udp::socket &aSocket) : _buffer()
{
    aSocket.async_receive_from(
        boost::asio::buffer(_buffer),
        _remoteEndpoint,
        boost::bind(&SingleRequestListener::receiveRequest, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
    aIoContext.run();
}

void SingleRequestListener::receiveRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
{
    (void)aError;
    (void)aBytesTransferred;

    std::string result(_buffer.data(), aBytesTransferred);
    std::cout << "Received " << result << " from " << _remoteEndpoint << std::endl;
    NetworkHandler::getInstance();
}
