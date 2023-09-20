#include <boost/asio.hpp>

#ifndef NETWORKHANDLER_HPP
    #define NETWORKHANDLER_HPP

using boost::asio::ip::udp;

class NetworkHandler
{
    private:
        boost::asio::io_context _ioContext;
        udp::endpoint _serverEndpoint;
        udp::resolver _resolver;
        udp::socket _socket;

    public:
        /**
         * @brief Connect to the server
         * @param host The ip address of the server (without port)
         */
        explicit NetworkHandler(const std::string &);
        ~NetworkHandler() = default;

        /**
         * @brief Listen to the server
         */
        void listen();

        /**
         * @brief Send a message to the server
         * @param buffer The message to send
         */
        void send(const boost::asio::const_buffer &);
};

#endif
