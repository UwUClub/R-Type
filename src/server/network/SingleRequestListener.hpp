#include <boost/asio.hpp>
#include <boost/array.hpp>

#ifndef REQUESTLISTENER_HPP
#define NETWORKHANDLER_HPP

#define BUFFER_SIZE 128

using boost::asio::ip::udp;

class SingleRequestListener {

    private:
    boost::array<char, BUFFER_SIZE> _buffer;
    udp::endpoint _remoteEndpoint;

    public:
    explicit SingleRequestListener(boost::asio::io_context &, udp::socket &);
    ~SingleRequestListener() = default;

    void receiveRequest(const boost::system::error_code &, std::size_t);
};

#endif
