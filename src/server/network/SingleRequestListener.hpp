#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "NetworkHandler.hpp"
#include "Packets.hpp"

#ifndef REQUESTLISTENER_HPP
    #define NETWORKHANDLER_HPP

constexpr unsigned short BUFFER_SIZE = 28;

using boost::asio::ip::udp;

class SingleRequestListener
{
    private:
        boost::array<char, BUFFER_SIZE> _buffer;
        udp::endpoint _remoteEndpoint;
        NetworkHandler *_networkHandler;

    public:
        explicit SingleRequestListener(boost::asio::io_context &, udp::socket &, NetworkHandler *);
        ~SingleRequestListener() = default;

        void receiveRequest(const boost::system::error_code &, std::size_t);
};

#endif
