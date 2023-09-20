#include <boost/asio.hpp>

#ifndef ClientNetworkHandler_HPP
    #define ClientNetworkHandler_HPP

using boost::asio::ip::udp;

class ClientNetworkHandler
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
        explicit ClientNetworkHandler(const std::string &);
        ~ClientNetworkHandler() = default;

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
