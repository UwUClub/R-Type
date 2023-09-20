#include <boost/asio.hpp>
#include <map>
#include <iostream>

#ifndef NETWORKHANDLER_HPP
    #define NETWORKHANDLER_HPP

    #define UDP_PORT 13

using boost::asio::ip::udp;

class NetworkHandler
{
    private:
        boost::asio::ip::port_type _port = UDP_PORT;
        boost::asio::io_context _ioContext;
        udp::socket _socket;
        // std::map<udp::endpoint, Player> _clients;

        /**
         * @brief Launch the server
         * @param port The port to listen to
         */
        explicit NetworkHandler();

    public:
        /**
         * @brief Destroy the NetworkHandler object
         */
        ~NetworkHandler() = default;

        /**
         * @brief Get the instance of the singleton
         * @return NetworkHandler & The instance of the singleton
         */
        static NetworkHandler &getInstance()
        {
            static NetworkHandler instance;
            return instance;
        }

        /**
         * @brief Listen to clients
         */
        void listen();

        /**
         * @brief Send a message to the server
         * @param buffer The message to send
         * @param clientId The id of the client to send the message to
         */
        void send(const boost::asio::const_buffer, size_t);
};

#endif
